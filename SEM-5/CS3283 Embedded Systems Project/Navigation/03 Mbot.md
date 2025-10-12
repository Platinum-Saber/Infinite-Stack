
```cpp
// MBot_Universal.ino
// Universal M-Bot code without MakeBlock library dependency
// Compatible with Arduino Uno/Nano and mCore boards
// Upload this to the M-Bot, NOT the ESP32

// Robot identification - CHANGE THIS FOR EACH ROBOT
const int ROBOT_ID = 1; // Set to 1 for Robot 1, 2 for Robot 2

// Pin definitions for mCore/Arduino Uno compatibility
// Motor Driver Pins (L298N or similar)
#define MOTOR_LEFT_PWM    6   // Left motor PWM (speed)
#define MOTOR_LEFT_DIR1   7   // Left motor direction 1
#define MOTOR_LEFT_DIR2   8   // Left motor direction 2
#define MOTOR_RIGHT_PWM   5   // Right motor PWM (speed)
#define MOTOR_RIGHT_DIR1  4   // Right motor direction 1
#define MOTOR_RIGHT_DIR2  2   // Right motor direction 2

// Ultrasonic Sensor Pins
#define ULTRASONIC_TRIG   12  // Trigger pin
#define ULTRASONIC_ECHO   13  // Echo pin

// RGB LED Pins (if available)
#define LED_RED_PIN       9   // Red LED
#define LED_GREEN_PIN     10  // Green LED  
#define LED_BLUE_PIN      11  // Blue LED

// Buzzer Pin
#define BUZZER_PIN        3   // Buzzer/Speaker

// Communication with ESP32 (Hardware Serial on Uno)
// Use pins 0 (RX) and 1 (TX) - these are connected to ESP32

// Navigation parameters
int base_speed = 120;
int turn_speed = 150;
float safe_distance = 25.0; // cm
bool autonomous_mode = true;
bool emergency_stop = false;

// Command structure
struct Command {
    char type; // 'M' for move, 'T' for turn, 'S' for stop, 'A' for autonomous, 'E' for emergency
    float value; // speed or angle
};

// Status variables
unsigned long last_command_time = 0;
unsigned long last_sensor_send = 0;
unsigned long last_status_flash = 0;
bool status_flash_state = false;

void setup() {
    // Initialize serial communication with ESP32
    Serial.begin(9600);
    
    // Initialize motor pins
    pinMode(MOTOR_LEFT_PWM, OUTPUT);
    pinMode(MOTOR_LEFT_DIR1, OUTPUT);
    pinMode(MOTOR_LEFT_DIR2, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR1, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR2, OUTPUT);
    
    // Initialize ultrasonic sensor pins
    pinMode(ULTRASONIC_TRIG, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);
    
    // Initialize LED pins
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    
    // Initialize buzzer
    pinMode(BUZZER_PIN, OUTPUT);
    
    // Startup sequence
    set_rgb_color(0, 0, 255); // Blue for Robot 1, Red for Robot 2 (see below)
    if (ROBOT_ID == 2) {
        set_rgb_color(255, 0, 0); // Red for Robot 2
    }
    
    // Startup sound - different pitch for each robot
    play_tone(1000 + (ROBOT_ID * 200), 300);
    
    // Send initialization message to ESP32
    Serial.print("INIT:Robot");
    Serial.println(ROBOT_ID);
    
    delay(1000);
    
    // Ready state - green LED
    set_rgb_color(0, 255, 0);
    
    Serial.print("STATUS:Robot");
    Serial.print(ROBOT_ID);
    Serial.println(" Ready");
}

void loop() {
    // Check for commands from ESP32
    if (Serial.available()) {
        Command cmd = read_command();
        execute_command(cmd);
        last_command_time = millis();
    }
    
    // Autonomous safety check
    if (autonomous_mode && !emergency_stop) {
        safety_check();
    }
    
    // Send sensor data to ESP32
    send_sensor_data();
    
    // Update status indicators
    update_status_indicators();
    
    // Command timeout check
    check_command_timeout();
    
    delay(50);
}

Command read_command() {
    Command cmd;
    String data = Serial.readStringUntil('\n');
    data.trim();
    
    if (data.length() > 0) {
        cmd.type = data.charAt(0);
        if (data.length() > 1) {
            cmd.value = data.substring(1).toFloat();
        } else {
            cmd.value = 0;
        }
    } else {
        cmd.type = 'S'; // Default to stop
        cmd.value = 0;
    }
    
    return cmd;
}

void execute_command(Command cmd) {
    switch (cmd.type) {
        case 'M': // Move forward/backward
            if (!emergency_stop) {
                move_robot(cmd.value);
            }
            break;
            
        case 'T': // Turn left/right
            if (!emergency_stop) {
                turn_robot(cmd.value);
            }
            break;
            
        case 'S': // Stop
            stop_robot();
            emergency_stop = false;
            break;
            
        case 'A': // Set autonomous mode
            autonomous_mode = (cmd.value > 0);
            if (autonomous_mode) {
                set_rgb_color(0, 255, 0); // Green for autonomous
            } else {
                set_rgb_color(255, 255, 0); // Yellow for manual
            }
            break;
            
        case 'E': // Emergency stop
            emergency_stop = true;
            stop_robot();
            set_rgb_color(255, 0, 0); // Red for emergency
            play_tone(2000, 200);
            Serial.println("EMERGENCY:Activated");
            break;
            
        case 'R': // Reset emergency
            emergency_stop = false;
            set_rgb_color(0, 255, 0); // Green for normal
            Serial.println("STATUS:Emergency Reset");
            break;
            
        default:
            // Unknown command - stop for safety
            stop_robot();
            Serial.print("ERROR:Unknown command: ");
            Serial.println(cmd.type);
            break;
    }
}

void move_robot(float speed) {
    if (emergency_stop) {
        return;
    }
    
    // Clamp speed to safe limits
    speed = constrain(speed, -255, 255);
    
    // Check for immediate obstacles before moving forward
    if (speed > 0) {
        float distance = read_ultrasonic();
        if (distance < safe_distance && distance > 0) {
            emergency_stop = true;
            stop_robot();
            set_rgb_color(255, 0, 0);
            play_tone(1500, 100);
            Serial.println("EMERGENCY:Obstacle detected");
            return;
        }
    }
    
    // Apply motor commands
    if (speed >= 0) {
        // Forward motion
        motor_left_forward(abs(speed));
        motor_right_forward(abs(speed));
        set_rgb_color(0, 255, 0); // Green for forward
    } else {
        // Backward motion
        motor_left_backward(abs(speed));
        motor_right_backward(abs(speed));
        set_rgb_color(255, 165, 0); // Orange for backward
    }
}

void turn_robot(float angle) {
    if (emergency_stop) {
        return;
    }
    
    // Convert angle to time-based turn
    // Positive angle = right turn, negative = left turn
    float turn_time = abs(angle) * 8; // Calibration factor (adjust as needed)
    turn_time = constrain(turn_time, 50, 1000); // Limit turn time
    
    if (angle > 0) { // Turn right
        motor_left_forward(turn_speed);
        motor_right_backward(turn_speed * 0.9); // Slight asymmetry for better turning
        set_rgb_color(0, 0, 255); // Blue for right turn
    } else { // Turn left
        motor_left_backward(turn_speed * 0.9);
        motor_right_forward(turn_speed);
        set_rgb_color(255, 255, 0); // Yellow for left turn
    }
    
    delay(turn_time);
    stop_robot();
}

void stop_robot() {
    motor_left_stop();
    motor_right_stop();
    
    if (emergency_stop) {
        set_rgb_color(255, 0, 0); // Red for emergency stop
    } else {
        set_rgb_color(255, 255, 255); // White for normal stop
    }
}

// Motor control functions
void motor_left_forward(int speed) {
    digitalWrite(MOTOR_LEFT_DIR1, HIGH);
    digitalWrite(MOTOR_LEFT_DIR2, LOW);
    analogWrite(MOTOR_LEFT_PWM, speed);
}

void motor_left_backward(int speed) {
    digitalWrite(MOTOR_LEFT_DIR1, LOW);
    digitalWrite(MOTOR_LEFT_DIR2, HIGH);
    analogWrite(MOTOR_LEFT_PWM, speed);
}

void motor_left_stop() {
    digitalWrite(MOTOR_LEFT_DIR1, LOW);
    digitalWrite(MOTOR_LEFT_DIR2, LOW);
    analogWrite(MOTOR_LEFT_PWM, 0);
}

void motor_right_forward(int speed) {
    digitalWrite(MOTOR_RIGHT_DIR1, HIGH);
    digitalWrite(MOTOR_RIGHT_DIR2, LOW);
    analogWrite(MOTOR_RIGHT_PWM, speed);
}

void motor_right_backward(int speed) {
    digitalWrite(MOTOR_RIGHT_DIR1, LOW);
    digitalWrite(MOTOR_RIGHT_DIR2, HIGH);
    analogWrite(MOTOR_RIGHT_PWM, speed);
}

void motor_right_stop() {
    digitalWrite(MOTOR_RIGHT_DIR1, LOW);
    digitalWrite(MOTOR_RIGHT_DIR2, LOW);
    analogWrite(MOTOR_RIGHT_PWM, 0);
}

// Ultrasonic sensor function
float read_ultrasonic() {
    // Send trigger pulse
    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);
    
    // Read echo pulse
    long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000); // 30ms timeout
    
    // Calculate distance in cm
    float distance = duration * 0.034 / 2;
    
    // Return 0 if out of range or timeout
    if (distance > 400 || distance == 0) {
        return 0;
    }
    
    return distance;
}

// RGB LED control
void set_rgb_color(int red, int green, int blue) {
    // Map 0-255 values to PWM output
    analogWrite(LED_RED_PIN, red);
    analogWrite(LED_GREEN_PIN, green);
    analogWrite(LED_BLUE_PIN, blue);
}

// Buzzer control
void play_tone(int frequency, int duration) {
    // Generate tone using digitalWrite (simple square wave)
    long period = 1000000L / frequency;
    long half_period = period / 2;
    long cycles = ((long)frequency * duration) / 1000;
    
    for (long i = 0; i < cycles; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(half_period);
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(half_period);
    }
}

void safety_check() {
    float distance = read_ultrasonic();
    
    // Check for obstacles
    if (distance < safe_distance && distance > 0) {
        emergency_stop = true;
        stop_robot();
        
        // Alert sound
        play_tone(1500, 50);
        
        // Send emergency status to ESP32
        Serial.println("EMERGENCY:Obstacle detected");
        
        // Visual indication
        set_rgb_color(255, 0, 0);
    }
}

void send_sensor_data() {
    unsigned long now = millis();
    
    if (now - last_sensor_send > 100) { // Send every 100ms
        float distance = read_ultrasonic();
        
        // Format: SENSOR:distance,autonomous,emergency,robot_id
        Serial.print("SENSOR:");
        Serial.print(distance);
        Serial.print(",");
        Serial.print(autonomous_mode ? 1 : 0);
        Serial.print(",");
        Serial.print(emergency_stop ? 1 : 0);
        Serial.print(",");
        Serial.println(ROBOT_ID);
        
        last_sensor_send = now;
    }
}

void update_status_indicators() {
    unsigned long now = millis();
    
    // Robot identification flash every 3 seconds
    if (now - last_status_flash > 3000) {
        // Flash robot ID number of times
        for (int i = 0; i < ROBOT_ID; i++) {
            set_rgb_color(255, 255, 255); // White flash
            delay(150);
            set_rgb_color(0, 0, 0); // Off
            delay(150);
        }
        
        // Return to status color
        if (emergency_stop) {
            set_rgb_color(255, 0, 0); // Red for emergency
        } else if (autonomous_mode) {
            set_rgb_color(0, 255, 0); // Green for autonomous
        } else {
            set_rgb_color(255, 255, 0); // Yellow for manual
        }
        
        last_status_flash = now;
    }
}

void check_command_timeout() {
    unsigned long now = millis();
    
    // If no commands received for 2 seconds, go to safe state
    if (now - last_command_time > 2000 && last_command_time > 0) {
        if (!emergency_stop) {
            stop_robot();
            Serial.println("STATUS:Command timeout - stopping");
        }
    }
}

// Additional utility functions
void run_diagnostics() {
    // System diagnostics
    Serial.print("DIAG:Robot");
    Serial.print(ROBOT_ID);
    Serial.print(",Ultrasonic:");
    Serial.print(read_ultrasonic());
    Serial.print(",Motors:OK,Emergency:");
    Serial.print(emergency_stop ? "YES" : "NO");
    Serial.print(",Autonomous:");
    Serial.println(autonomous_mode ? "YES" : "NO");
}

void calibrate_motors() {
    // Motor calibration routine - run forward, backward, turn tests
    Serial.println("STATUS:Starting motor calibration");
    
    // Test forward
    motor_left_forward(100);
    motor_right_forward(100);
    delay(1000);
    stop_robot();
    delay(500);
    
    // Test backward
    motor_left_backward(100);
    motor_right_backward(100);
    delay(1000);
    stop_robot();
    delay(500);
    
    // Test turn left
    motor_left_backward(100);
    motor_right_forward(100);
    delay(500);
    stop_robot();
    delay(500);
    
    // Test turn right
    motor_left_forward(100);
    motor_right_backward(100);
    delay(500);
    stop_robot();
    
    Serial.println("STATUS:Motor calibration complete");
}

// Emergency procedures
void emergency_procedure() {
    // Full emergency stop procedure
    emergency_stop = true;
    stop_robot();
    
    // Alert sequence
    for (int i = 0; i < 3; i++) {
        set_rgb_color(255, 0, 0);
        play_tone(2000, 200);
        delay(300);
        set_rgb_color(0, 0, 0);
        delay(200);
    }
    
    set_rgb_color(255, 0, 0);
    Serial.println("EMERGENCY:Full stop activated");
}
```
