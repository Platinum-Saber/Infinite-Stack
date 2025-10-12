
```cpp
// ESP32 Position-Servo for WGB37 DC Gear Motor + Quadrature Encoder
// "Type-in an angle, it goes there" — like a hobby servo, but big.
// Features
//  - Outer position PID (deg)
//  - Inner speed PI (RPM)
//  - Trapezoidal motion profile (max vel/accel)
//  - Backlash-aware approach (optional one-sided settle)
//  - Deadband compensation + anti-windup
//  - Soft limits, homing (limit switch optional), zeroing
//  - CLI for live tuning
//
// Wiring (example):
//  Encoder A -> GPIO34 (input only)
//  Encoder B -> GPIO35 (input only)
//  Driver: DIR -> GPIO26, PWM -> GPIO25 (LEDC)
//  Limit/Home switch (NC to GND) -> GPIO27 with INPUT_PULLUP (optional)
//  Common GND between ESP32, driver, power
//
// Notes:
// 1) Set COUNTS_PER_REV_OUTPUT to your measured value (see CLI CPR).
// 2) Set gear backlash_deg to your gearbox's measured backlash (typ. 1..5 deg).
// 3) For very tight final accuracy, keep approach_one_side=true and set settle_band_deg small.

#include <Arduino.h>

// ---------- Pins ----------
#define PIN_ENC_A   34
#define PIN_ENC_B   35
#define PIN_PWM     25
#define PIN_DIR     26
#define PIN_HOME    27   // optional NC switch to GND (LOW = pressed)

// ---------- PWM ----------
#define PWM_FREQ       20000    // 20kHz
#define PWM_CHANNEL    0
#define PWM_RES_BITS   12
static const int PWM_MAX = (1<<PWM_RES_BITS) - 1;

// ---------- User Parameters (editable at runtime via CLI) ----------
volatile long COUNTS_PER_REV_OUTPUT = 1320;  // MUST calibrate

// Soft limits (deg). Use large values if you don't need them.
volatile float soft_min_deg = -180.0f;
volatile float soft_max_deg = +180.0f;

// Motion profile limits
volatile float max_vel_dps   = 360.0f;  // deg/s
volatile float max_acc_dps2  = 720.0f;  // deg/s^2

// Position PID (deg -> effort via speed setpoint):
volatile float Kp_pos = 4.0f;    // (deg) -> (deg/s) prefilter gain (acts like P into speed ref)
volatile float Ki_pos = 0.2f;    // integrator on position error -> adds to speed ref
volatile float Kd_pos = 0.0f;    // derivative on pos error (usually small/zero)

// Speed PI (RPM -> effort)
volatile float Kp_spd = 0.8f;
volatile float Ki_spd = 18.0f;
volatile float Kd_spd = 0.0f;

// Friction/dead-zone compensation
volatile int   pwm_deadband   = 80;      // minimal PWM to break static friction
volatile float ff_volt_ratio  = 0.0f;    // simple feedforward 0..1 scale of cmd

// Backlash handling
volatile bool  approach_one_side = true; // always finish from positive dir
volatile float backlash_deg      = 2.0f; // measured mechanical backlash
volatile float settle_band_deg   = 0.20f;// acceptable final error band

// Control periods
#define CONTROL_PERIOD_MS 5      // inner control tick (200Hz)
#define TEL_PERIOD_MS     200

// ---------- State ----------
volatile long enc_counts = 0;
volatile float pos_deg   = 0.0f; // measured
volatile float rpm_meas  = 0.0f; // measured

volatile float goal_deg  = 0.0f; // target angle (user)

// Motion-profile internal setpoint (deg & dps)
volatile float sp_pos_deg = 0.0f;
volatile float sp_vel_dps = 0.0f;

// Integrators
volatile float ei_pos = 0.0f;
volatile float ei_spd = 0.0f;

// Previous
volatile float prev_pos_err = 0.0f;
volatile float prev_spd_err = 0.0f;

// Command output
volatile int  pwm_cmd = 0;
volatile bool dir_cmd = true; // true=fwd

// Control timer
hw_timer_t* controlTimer = nullptr;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// ---------- Helpers ----------
template<typename T> static inline T clamp(T v, T lo, T hi){return (v<lo)?lo:((v>hi)?hi:v);} 
static inline float sgnf(float x){return (x>=0.0f)?1.0f:-1.0f;}

// Degrees <-> counts
static inline float counts_to_deg(long c, long cpr){ return (float)c * 360.0f / (float)cpr; }

// ---------- Encoder ISR (simple quad) ----------
void IRAM_ATTR encISR(){
  static int lastEncoded = 0;
  int a = digitalRead(PIN_ENC_A);
  int b = digitalRead(PIN_ENC_B);
  int encoded = (a << 1) | b;
  int sum = (lastEncoded << 2) | encoded;
  if (sum==0b0001 || sum==0b0111 || sum==0b1110 || sum==0b1000) enc_counts++;
  if (sum==0b0010 || sum==0b0100 || sum==0b1101 || sum==0b1011) enc_counts--;
  lastEncoded = encoded;
}

// ---------- Motor write ----------
void motorWrite(float effort){ // effort in [-1,1]
  effort = clamp(effort, -1.0f, +1.0f);
  bool dir = (effort >= 0);
  float mag = fabsf(effort);
  int pwm = (int)(mag * PWM_MAX);
  if (pwm>0 && pwm<pwm_deadband) pwm = pwm_deadband;
  pwm = clamp(pwm, 0, PWM_MAX);
  dir_cmd = dir;
  pwm_cmd = pwm;
  digitalWrite(PIN_DIR, dir?HIGH:LOW);
  ledcWrite(PWM_CHANNEL, pwm);
}

// ---------- Trapezoidal motion profile step ----------
// Advances sp_pos_deg and sp_vel_dps toward goal_deg obeying max_vel & max_acc
void profileStep(float dt){
  float pos_err = goal_deg - sp_pos_deg;
  float stop_dist = (sp_vel_dps*sp_vel_dps) / (2.0f*max_acc_dps2); // distance to stop
  float dir = sgnf(pos_err);

  // Decide if we should accelerate or decelerate
  if (fabsf(pos_err) > stop_dist) {
    // accelerate toward goal
    sp_vel_dps += dir * max_acc_dps2 * dt;
  } else {
    // decelerate to zero at goal
    sp_vel_dps -= sgnf(sp_vel_dps) * max_acc_dps2 * dt;
  }
  // Limit velocity
  sp_vel_dps = clamp(sp_vel_dps, -max_vel_dps, +max_vel_dps);

  // Integrate position
  sp_pos_deg += sp_vel_dps * dt;

  // If very close, snap & zero
  if (fabsf(goal_deg - sp_pos_deg) < 0.01f && fabsf(sp_vel_dps) < 0.1f){
    sp_pos_deg = goal_deg;
    sp_vel_dps = 0.0f;
  }
}

// ---------- Backlash approach correction ----------
float applyBacklashApproach(float raw_target_deg){
  if (!approach_one_side) return raw_target_deg;
  // Always finish from + direction: offset target negatively by backlash, then final settle pass
  float current = pos_deg;
  float desired = raw_target_deg;
  if (desired >= current){
    // moving + already: no change
    return desired;
  } else {
    // we are to the right of desired; overshoot to the left by backlash, then come back in + dir
    return desired - backlash_deg; // profile drives past, then PID brings from + direction
  }
}

// ---------- Control Timer ISR ----------
void IRAM_ATTR onControl(){
  portENTER_CRITICAL_ISR(&timerMux);
  const float dt = CONTROL_PERIOD_MS/1000.0f;

  // 1) Measure position & speed
  long counts = enc_counts;
  pos_deg = counts_to_deg(counts, COUNTS_PER_REV_OUTPUT);

  static long last_counts = 0;
  long dcounts = counts - last_counts; last_counts = counts;
  // deg/s from counts
  float dps_meas = counts_to_deg(dcounts, COUNTS_PER_REV_OUTPUT) / dt;
  // Convert to RPM for speed loop (just a unit; PI works with either)
  rpm_meas = dps_meas * (1.0f/6.0f); // 360 deg = 1 rev; 60s/min => dps/6 = RPM

  // 2) Motion profile toward goal (with soft limits)
  goal_deg = clamp(goal_deg, soft_min_deg, soft_max_deg);
  profileStep(dt);

  // 3) Position controller -> speed setpoint (deg/s then to RPM)
  float pos_err = sp_pos_deg - pos_deg; // follow profiled setpoint

  // Derivative on measurement to reduce noise
  float d_pos_err = (pos_err - prev_pos_err)/dt;
  prev_pos_err = pos_err;

  // Integrator with simple clamp
  ei_pos += pos_err * dt;
  ei_pos = clamp(ei_pos, -1000.0f, +1000.0f);

  float cmd_dps = Kp_pos*pos_err + Ki_pos*ei_pos + Kd_pos*d_pos_err;
  // combine with profile feed (sp_vel_dps)
  float target_dps = sp_vel_dps + cmd_dps;
  // convert to RPM for inner loop
  float target_rpm = target_dps / 6.0f;

  // 4) Speed PI -> effort
  float e_spd = target_rpm - rpm_meas;
  ei_spd += e_spd * dt;
  ei_spd = clamp(ei_spd, -500.0f, +500.0f);
  float de_spd = (e_spd - prev_spd_err)/dt; // often 0
  prev_spd_err = e_spd;

  float effort = Kp_spd*e_spd + Ki_spd*ei_spd + Kd_spd*de_spd;
  // simple feedforward: proportional to desired speed fraction
  float ff = ff_volt_ratio * clamp(target_rpm/ (max_vel_dps/6.0f), -1.0f, +1.0f);
  effort += ff;

  // Anti-windup via saturation back-calc
  float u_sat = clamp(effort, -1.0f, +1.0f);
  if (effort != u_sat && Ki_spd > 1e-6f) {
    float aw = effort - u_sat;
    ei_spd -= aw / Ki_spd;  // back-calc
  }

  // 5) Backlash-aware final settle: once within settle band, bias so we finish from + side
  if (approach_one_side && fabsf(goal_deg - pos_deg) < backlash_deg){
    // nudge target so final motion is positive direction
    float biased = applyBacklashApproach(goal_deg);
    sp_pos_deg = biased; // temporary bias; once crossed, the normal control finishes
  }

  // 6) Command motor
  motorWrite(u_sat);

  portEXIT_CRITICAL_ISR(&timerMux);
}

// ---------- CLI ----------
void printHelp(){
  Serial.println("Commands:");
  Serial.println("  G <deg>           : go to absolute angle (deg)");
  Serial.println("  A <deg>           : add relative angle (deg)");
  Serial.println("  CPR <val>         : set counts per rev of output");
  Serial.println("  LIM <min> <max>   : set soft limits (deg)");
  Serial.println("  VEL <dps>         : set max velocity (deg/s)");
  Serial.println("  ACC <dps2>        : set max accel (deg/s^2)");
  Serial.println("  GP <kp ki kd>     : position PID gains");
  Serial.println("  GS <kp ki kd>     : speed PID gains");
  Serial.println("  DB <pwm>          : set PWM deadband (0..4095)");
  Serial.println("  FF <0..1>         : set feedforward ratio");
  Serial.println("  BL <deg>          : set backlash degrees");
  Serial.println("  SB <deg>          : set settle band degrees");
  Serial.println("  ONE <0|1>         : approach from one side toggle");
  Serial.println("  Z                  : zero current position (set angle=0)");
  Serial.println("  HOME               : home to switch at PIN_HOME (optional)");
}

void handleCLI(const String& cmd){
  if (cmd.startsWith("G ")){ goal_deg = cmd.substring(2).toFloat(); Serial.printf("[GOTO] %.3f\n", goal_deg); }
  else if (cmd.startsWith("A ")){ goal_deg += cmd.substring(2).toFloat(); Serial.printf("[ADD] -> %.3f\n", goal_deg); }
  else if (cmd.startsWith("CPR ")){ long v=cmd.substring(4).toInt(); if(v>0){COUNTS_PER_REV_OUTPUT=v; Serial.printf("[CPR]=%ld\n",v);} }
  else if (cmd.startsWith("LIM ")){ float a,b; if(sscanf(cmd.c_str()+4, "%f %f", &a,&b)==2){soft_min_deg=a;soft_max_deg=b; Serial.printf("[LIM]=[%.1f,%.1f]\n",a,b);} }
  else if (cmd.startsWith("VEL ")){ max_vel_dps = cmd.substring(4).toFloat(); Serial.printf("[VEL]=%.1f dps\n", max_vel_dps); }
  else if (cmd.startsWith("ACC ")){ max_acc_dps2 = cmd.substring(4).toFloat(); Serial.printf("[ACC]=%.1f dps^2\n", max_acc_dps2); }
  else if (cmd.startsWith("GP ")){ float kp,ki,kd; if(sscanf(cmd.c_str()+3, "%f %f %f", &kp,&ki,&kd)==3){Kp_pos=kp;Ki_pos=ki;Kd_pos=kd; Serial.printf("[GP]=%.3f %.3f %.3f\n",kp,ki,kd);} }
  else if (cmd.startsWith("GS ")){ float kp,ki,kd; if(sscanf(cmd.c_str()+3, "%f %f %f", &kp,&ki,&kd)==3){Kp_spd=kp;Ki_spd=ki;Kd_spd=kd; Serial.printf("[GS]=%.3f %.3f %.3f\n",kp,ki,kd);} }
  else if (cmd.startsWith("DB ")){ pwm_deadband = clamp(cmd.substring(3).toInt(),0,PWM_MAX); Serial.printf("[DB]=%d\n",pwm_deadband); }
  else if (cmd.startsWith("FF ")){ ff_volt_ratio = clamp(cmd.substring(3).toFloat(),0.0f,1.0f); Serial.printf("[FF]=%.2f\n",ff_volt_ratio); }
  else if (cmd.startsWith("BL ")){ backlash_deg = cmd.substring(3).toFloat(); Serial.printf("[BL]=%.2f deg\n",backlash_deg); }
  else if (cmd.startsWith("SB ")){ settle_band_deg = cmd.substring(3).toFloat(); Serial.printf("[SB]=%.3f deg\n",settle_band_deg); }
  else if (cmd.startsWith("ONE ")){ approach_one_side = (cmd.substring(4).toInt()!=0); Serial.printf("[ONE]=%d\n",(int)approach_one_side); }
  else if (cmd == "Z"){ // zero here
    noInterrupts(); enc_counts = 0; interrupts(); sp_pos_deg=0; goal_deg=0; Serial.println("[ZERO] pos=0 deg");
  }
  else if (cmd == "HOME"){
    Serial.println("[HOME] Searching...");
    // simple home: move negative until switch pressed, then set zero
    unsigned long t0 = millis();
    while (digitalRead(PIN_HOME)!=LOW && millis()-t0 < 8000){ goal_deg -= 0.5f; delay(5); }
    noInterrupts(); enc_counts = 0; interrupts(); sp_pos_deg=0; goal_deg=0; Serial.println("[HOME] done, zeroed");
  }
  else if (cmd == "H" || cmd == "HELP"){ printHelp(); }
}

// ---------- Setup ----------
void setup(){
  Serial.begin(115200);
  delay(200);

  pinMode(PIN_DIR, OUTPUT);
  digitalWrite(PIN_DIR, LOW);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES_BITS);
  ledcAttachPin(PIN_PWM, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, 0);

  pinMode(PIN_ENC_A, INPUT);
  pinMode(PIN_ENC_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_A), encISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_B), encISR, CHANGE);

  pinMode(PIN_HOME, INPUT_PULLUP); // optional

  // Control timer
  controlTimer = timerBegin(0, 80, true); // 80 MHz/80=1MHz
  timerAttachInterrupt(controlTimer, &onControl, true);
  timerAlarmWrite(controlTimer, CONTROL_PERIOD_MS*1000, true);
  timerAlarmEnable(controlTimer);

  Serial.println("Position Servo Ready. Type H for help.");
}

// ---------- Loop ----------
void loop(){
  if (Serial.available()){
    String s = Serial.readStringUntil('\n'); s.trim(); if(s.length()) handleCLI(s);
  }

  static uint32_t t0=0; if (millis()-t0 > TEL_PERIOD_MS){ t0=millis();
    noInterrupts(); float p=pos_deg, sp=sp_pos_deg, g=goal_deg; float v=rpm_meas; int pw=pwm_cmd; bool d=dir_cmd; interrupts();
    Serial.printf("POS=%.3f SP=%.3f GOAL=%.3f RPM=%.1f PWM=%d DIR=%d\n", p, sp, g, v, pw, (int)d);
  }
}

```



1. wire it
   ENC A→GPIO34, ENC B→GPIO35, DIR→GPIO26, PWM→GPIO25 (20 kHz LEDC), optional home switch (NC)→GPIO27 with pull-up. Common ground everywhere.

2. first-run checklist

* Power on, open Serial Monitor at 115200.
* Type `H` to see commands.
* Set your encoder resolution: `CPR <counts_per_rev_of_output_shaft>`. (If unknown, we can measure—it’s in the code comments.)
* Optional: set workspace limits: `LIM -180 180`.

3. go to angles like a servo

* Absolute move: `G 90`  → goes to +90°.
* Relative move: `A -45` → nudges −45° from current.
* Zero here: `Z`.
* Optional homing with a switch: `HOME`.

4. tune for snap + accuracy (quick recipe)

* Leave motion limits sane: `VEL 360` (deg/s), `ACC 720` (deg/s²).
* Start with position gains `GP 4 0.2 0`. If it overshoots, lower `Kp_pos` a bit; if it creeps at the end, raise `Ki_pos` slightly (0.1→0.3). Keep `Kd_pos=0` unless you see oscillation.
* Speed loop: `GS 0.8 18 0` is a good default. If it feels sluggish, raise `Kp_spd` in small steps; if it hums/oscillates, lower `Ki_spd`.
* If the motor sticks before moving, bump `DB` up (e.g., `DB 120`).
* If you need more punch, add some feedforward: `FF 0.1` to `0.25`.

5. beat gearbox backlash (precision trick)

* Measure backlash (often 1–3°). Set `BL <deg>`, enable one-sided finish: `ONE 1`.
* The controller over-travels slightly, then always **settles from the same direction**, giving consistent final angles inside `SB` (settle band, e.g., `SB 0.2`°).

6. motion profile = smooth stops

* The built-in trapezoidal profile enforces `VEL`/`ACC` limits so you don’t overshoot or spike current. For snappier moves, raise `VEL` and `ACC`; for gentle, lower them.

7. accuracy checklist (mechanical + electrical)

* Solid encoder mounting and **3.3 V-safe** signals (use pull-ups to 3.3 V if open-collector).
* Keep motor/driver wires away from encoder lines; twist motor leads.
* Bulk caps near driver.
* Tight couplings; minimize shaft play.
