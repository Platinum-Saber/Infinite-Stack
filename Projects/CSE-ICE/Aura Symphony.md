## Step 1: Understand the System Requirements

- **Power Calculation**:
    - Each bulb: 5W at 230V AC.
    - Total power: 100 bulbs × 5W = 500W.
    - Current per bulb: $( P = V \times I ), so ( I = \frac{P}{V} = \frac{5W}{230V} \approx 0.022A )$.
    - Current per row $(10 bulbs): ( 10 \times 0.022A = 0.22A )$.
    - Total current: $( 100 \times 0.022A = 2.2A )$.
    - Power source: 230V AC, capable of supplying at least 500W (ensure the circuit breaker supports ~3A for safety margin).
- **Control**:
    - 10 rows, each controlled by a relay.
    - ESP32 to switch relays on/off for patterns.
    - Music sync via audio input (e.g., microphone module or line-in) or pre-programmed patterns.
- **Safety**:
    - Use relays rated for 230V AC and at least 1A per row.
    - Ensure proper insulation and enclosures to prevent electric shock.
    - Consult a licensed electrician for AC wiring.

## Step 2: Gather Components

### Hardware

1. **Bulbs**:
    - 100 × 5W bulbs (e.g., LED or incandescent, 230V AC, with appropriate sockets like E27 or E14).
2. **Relays**:
    - 10 × 5V single-channel relay modules (rated for 250V AC, 10A, e.g., Songle SRD-05VDC-SL-C).
    - Active-low or active-high, depending on ESP32 GPIO logic (active-low is common).
3. **ESP32**:
    - ESP32-DevKitC or similar (e.g., NodeMCU ESP32).
    - At least 10 GPIO pins for relay control.
4. **Power Supply**:
    - 5V DC power supply for ESP32 and relay modules (e.g., 5V 2A USB adapter).
    - Ensure the 230V AC circuit can handle 500W (standard household wiring typically supports this).
5. **Audio Input (for Music Sync)**:
    - Option 1: Microphone module (e.g., MAX9814 or KY-038) for real-time audio detection.
    - Option 2: Line-in audio splitter to feed music signal to ESP32’s ADC pin.
6. **Wiring and Connectors**:
    - 230V-rated wires for AC connections (e.g., 1.5mm² copper wire).
    - Terminal blocks or WAGO connectors for secure AC wiring.
    - Jumper wires for low-voltage connections (ESP32 to relays).
7. **Enclosure**:
    - Non-conductive project box to house relays, ESP32, and wiring.
    - Ensure ventilation to prevent overheating.
8. **Prototyping**:
    - Breadboard or PCB for low-voltage connections.
    - Soldering kit for permanent setup.

### Tools

- Multimeter for testing voltages and continuity.
- Screwdrivers, wire strippers, and pliers.
- Oscilloscope or logic analyzer (optional) for debugging audio signals.

## Step 3: Design the Circuit

### Bulb Arrangement

- Arrange bulbs in a 10×10 grid (10 rows, 10 bulbs per row).
- Connect bulbs in each row in parallel:
    - Each bulb gets 230V AC.
    - Total current per row: 0.22A.
- Each row is controlled by one relay, which switches the 230V AC supply to the row.

### Relay Setup

- Use 10 relay modules, each controlling one row.
- Relay specs:
    - Coil: 5V DC (controlled by ESP32 GPIO).
    - Contacts: Rated for 250V AC, 10A (well above the 0.22A per row).
- Connect relays:
    - **AC Side**:
        - Common (COM) terminal: Connect to 230V AC live wire.
        - Normally Open (NO) terminal: Connect to the row’s bulbs.
        - Bulbs’ other terminal connects to AC neutral.
    - **DC Side**:
        - VCC: Connect to 5V DC power supply.
        - GND: Connect to common ground with ESP32.
        - IN: Connect to ESP32 GPIO pin (one per relay).

### ESP32 Connections

- Assign 10 GPIO pins (e.g., GPIO 4, 5, 15, 16, 17, 18, 19, 21, 22, 23) to control the 10 relays.
- Connect each GPIO to the IN pin of a relay module.
- Power the ESP32 via USB or a 5V DC supply, ensuring a common ground with the relay modules.
- If using audio input:
    - Microphone module: Connect analog output to ESP32 ADC pin (e.g., GPIO 34).
    - Line-in: Use a voltage divider to scale the audio signal to 0–3.3V for the ADC.

### Safety Notes

- **AC Wiring**: Use insulated connectors and ensure no exposed high-voltage wires.
- **Isolation**: Keep 230V AC and 5V DC circuits separate to avoid interference or damage.
- **Grounding**: Ensure the enclosure and any metal parts are grounded.
- **Fuse**: Add a 3A fuse on the AC input for overcurrent protection.

## Step 4: Assemble the Hardware

1. **Prototype on Breadboard**:
    - Connect ESP32 to one relay module and a single bulb (or LED for testing).
    - Test GPIO control before scaling to 10 relays.
2. **Wire the Bulbs**:
    - Mount bulbs in a grid (e.g., on a wooden or metal frame).
    - Wire each row in parallel using 230V-rated wires.
    - Connect each row to the NO terminal of its relay.
3. **Connect Relays**:
    - Wire the AC side: Live to COM, bulbs to NO, neutral to bulbs.
    - Wire the DC side: 5V and GND to relay modules, IN to ESP32 GPIOs.
4. **Power Supply**:
    - Connect the 5V DC supply to ESP32 and relays.
    - Verify the AC circuit is off during assembly.
5. **Enclosure**:
    - Mount relays, ESP32, and wiring in a non-conductive box.
    - Use cable glands for AC and DC wires entering the enclosure.
6. **Test Connections**:
    - Use a multimeter to check for shorts or incorrect wiring.
    - Power on the 5V DC circuit first, then the AC circuit (with caution).

## Step 5: Program the ESP32

### Software Requirements

- **IDE**: Arduino IDE or `PlatformIO` with ESP32 support.
- **Libraries**:
    - `Arduino.h` (core library).
    - `arduinoFFT` (optional, for audio frequency analysis).
- **Firmware**:
    - Control relays to create patterns.
    - Process audio input for music sync.

### Sample Code

Below is a basic ESP32 program to control 10 relays with predefined patterns and optional audio-based control using a microphone module.

```cpp
#include

// Relay pins (connected to IN pins of relay modules)  
int relayPins[10] = {4, 5, 15, 16, 17, 18, 19, 21, 22, 23};

// Audio input pin (e.g., microphone module)  
const int audioPin = 34;

// Pattern definitions  
void allOn() {  
	for (int i = 0; i < 10; i++) {  
		digitalWrite(relayPins[i], LOW); // Active-low relays  
	}  
}

void allOff() {  
	for (int i = 0; i < 10; i++) {  
		digitalWrite(relayPins[i], HIGH);  
	}  
}

void chasePattern() {  
	allOff();  
	for (int i = 0; i < 10; i++) {  
		digitalWrite(relayPins[i], LOW);  
		delay(100);  
		digitalWrite(relayPins[i], HIGH);  
	}  
}

void audioReactive() {  
	int audioValue = analogRead(audioPin); // Read audio signal (0–4095)  
	int threshold = 2000; // Adjust based on testing  
	if (audioValue > threshold) {  
		allOn();  
	} else {  
		allOff();  
	}  
}

void setup() {  
// Initialize relay pins  
	for (int i = 0; i < 10; i++) {  
		pinMode(relayPins[i], OUTPUT);  
		digitalWrite(relayPins[i], HIGH); // Relays off (active-low)  
	}  
	// Initialize audio pin  
	pinMode(audioPin, INPUT);  
	// Serial for debugging  
	Serial.begin(115200);  
}

void loop() {  
	// Example: Run different patterns  
	chasePattern();  
	delay(1000);  
	allOn();  
	delay(1000);  
	allOff();  
	delay(1000);  
	audioReactive();  
	delay(50); // Fast updates for audio  
}
```

### Code Explanation

- **Relays**: Controlled by 10 GPIO pins (active-low logic, typical for relay modules).
- **Patterns**:
    - `allOn()`: Turns all rows on.
    - `allOff()`: Turns all rows off.
    - `chasePattern()`: Lights rows sequentially.
    - `audioReactive()`: Turns lights on when audio amplitude exceeds a threshold.
- **Audio Input**: Reads analog values from a microphone module (adjust threshold based on your setup).
- **Loop**: Cycles through patterns and audio-reactive mode.

### Enhancements

- **FFT Analysis**: Use the arduinoFFT library to analyze audio frequencies (e.g., bass, mid, treble) and map them to specific rows.
- **Wi-Fi Control**: Add a web server on the ESP32 to control patterns remotely.
- **Pre-programmed Sequences**: Store music-specific patterns in arrays and trigger them via a button or serial input.

## Step 6: Sync with Music

### Option 1: Microphone Module

- Connect a microphone module (e.g., MAX9814) to GPIO 34 (ADC).
- Adjust gain and threshold in the code to detect beats or amplitude peaks.
- Example: Map low frequencies (bass) to rows 1–3, mids to 4–7, highs to 8–10 using FFT.

### Option 2: Line-In Audio

- Use an audio splitter to feed the music signal to the ESP32.
- Add a voltage divider (e.g., two 10kΩ resistors) to scale the signal to 0–3.3V.
- Process the signal similarly to the microphone input.

### Testing Sync

- Play music and monitor Serial output to tune thresholds.
- Use a simple beat-heavy track to verify pattern responsiveness.

## Step 7: Test and Debug

1. **Low-Voltage Test**:
    - Test ESP32 and relays with a multimeter or LEDs (instead of bulbs).
    - Verify GPIO signals toggle relays correctly.
2. **Single Row Test**:
    - Connect one row of bulbs and test with the AC circuit.
    - Ensure the relay switches the row on/off.
3. **Full System Test**:
    - Connect all rows and run the program.
    - Check for consistent patterns and audio response.
4. **Debugging**:
    - Use Serial.print to log audio values or relay states.
    - Check for relay chatter (add a small delay or capacitor if needed).

## Step 8: Deploy at the Event

- **Mounting**: Secure the bulb grid and enclosure at the venue.
- **Power**: Connect to a reliable 230V AC source with a circuit breaker.
- **Testing**: Run a full test with music before the event.
- **Backup**: Have spare relays, bulbs, and an ESP32 on hand.

## Safety Reminders

- **High Voltage**: Only work on AC wiring with the power off.
- **Electrician**: Consult a professional for AC installation and inspection.
- **Enclosure**: Ensure no exposed wires or terminals.
- **Fire Safety**: Use flame-retardant materials and keep a fire extinguisher nearby.

## Optional Enhancements

- **DMX Integration**: Add a DMX shield to interface with professional lighting controllers.
- **Bluetooth**: Use an HC-05 module to control patterns via a smartphone app.
- **RGB Bulbs**: Upgrade to smart bulbs for color control (requires different relays or drivers).

## Resources

- ESP32 Pinout: [Espressif Documentation](https://www.espressif.com/)
- Relay Module Guide: Search for “5V relay module Arduino tutorial”.
- Audio Processing: [Arduino FFT Library](https://github.com/kosme/arduinoFFT)