# Musical Lighting System with Line-In Audio and React App

This guide extends the previous musical lighting system (100 5W bulbs, 10 rows, ESP32 with relays) to use line-in audio for music synchronization and adds a React app to control and monitor the ESP32 over a local network.

## Step 1: Modify Hardware for Line-In Audio
### Hardware Requirements
- **Line-In Audio Input**:
  - 3.5mm audio splitter (to feed music from the source to both speakers and ESP32).
  - Stereo-to-mono adapter (optional, to simplify signal processing).
  - Voltage divider components:
    - Two 10kΩ resistors (to scale audio signal to 0–3.3V for ESP32 ADC).
    - 3.3V Zener diode (optional, for overvoltage protection).
  - 3.5mm audio jack or cable to connect to ESP32.
- **Existing Components** (from previous guide):
  - 100 × 5W bulbs (230V AC).
  - 10 × 5V relay modules (250V AC, 10A).
  - ESP32-DevKitC.
  - 5V DC power supply.
  - 230V AC circuit (500W capacity).
  - Wiring, enclosure, and safety components.

### Circuit Modification
1. **Line-In Connection**:
   - Connect the 3.5mm audio cable’s left or right channel (or mono output) to a voltage divider:
     - Resistor 1 (10kΩ): Audio signal to divider input.
     - Resistor 2 (10kΩ): Divider output to ground.
     - Output (junction of resistors): Connect to ESP32 ADC pin (e.g., GPIO 34).
   - Optional: Add a 3.3V Zener diode across the ADC pin to ground to clamp overvoltages.
   - Ground: Connect audio ground to ESP32 ground.
2. **Test the Signal**:
   - Use a multimeter or oscilloscope to verify the audio signal is 0–3.3V.
   - Play music and ensure the signal varies with audio amplitude.

### Safety Notes
- Keep low-voltage audio wiring separate from 230V AC circuits.
- Use insulated connectors for the audio cable to prevent shorts.

## Step 2: Update ESP32 Firmware
The ESP32 will:
- Process line-in audio to detect amplitude or frequency for lighting patterns.
- Host a web server to:
  - Accept commands (e.g., select pattern, turn on/off).
  - Stream status (e.g., current pattern, audio level).
- Connect to the local Wi-Fi network.

### Software Requirements
- **Arduino IDE** or **PlatformIO**.
- **Libraries**:
  - `WiFi.h`: For Wi-Fi connectivity.
  - `ESPAsyncWebServer.h`: For asynchronous web server.
  - `arduinoFFT.h`: For frequency analysis (optional).
- Install libraries via Arduino Library Manager or PlatformIO.

### ESP32 Code
Below is the updated ESP32 firmware to handle line-in audio, control relays, and serve a WebSocket-based API for the React app.

```cpp

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <arduinoFFT.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Relay pins
int relayPins[10] = {4, 5, 15, 16, 17, 18, 19, 21, 22, 23};

// Audio input pin
const int audioPin = 34;

// Web server and WebSocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Pattern states
enum Pattern { OFF, ALL_ON, CHASE, AUDIO_REACTIVE };
Pattern currentPattern = OFF;

// Audio processing
#define SAMPLES 64
#define SAMPLING_FREQ 10000 // Hz
arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long lastSampleTime = 0;
float bassEnergy = 0;

void allOn() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(relayPins[i], LOW); // Active-low
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
    if (currentPattern != CHASE) break;
  }
}

void audioReactive() {
  // Sample audio
  if (micros() - lastSampleTime >= 1000000 / SAMPLING_FREQ) {
    for (int i = 0; i < SAMPLES; i++) {
      vReal[i] = analogRead(audioPin) / 4095.0 * 3.3;
      vImag[i] = 0;
    }
    lastSampleTime = micros();

    // Perform FFT
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    // Calculate bass energy (0–200 Hz)
    bassEnergy = 0;
    for (int i = 2; i < 10; i++) { // Approx. 0–200 Hz
      bassEnergy += vReal[i];
    }
    bassEnergy /= 8;

    // Map bass energy to rows
    int activeRows = map(bassEnergy, 0, 50, 0, 10); // Adjust based on testing
    for (int i = 0; i < 10; i++) {
      digitalWrite(relayPins[i], i < activeRows ? LOW : HIGH);
    }
  }
}

// WebSocket event handler
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  } else if (type == WS_EVT_DATA) {
    String message = "";
    for (size_t i = 0; i < len; i++) {
      message += (char)data[i];
    }
    if (message == "off") currentPattern = OFF;
    else if (message == "all_on") currentPattern = ALL_ON;
    else if (message == "chase") currentPattern = CHASE;
    else if (message == "audio_reactive") currentPattern = AUDIO_REACTIVE;
  }
}

// Send status to all WebSocket clients
void sendStatus() {
  String status = "{\"pattern\":\"" + String(currentPattern) + "\",\"bassEnergy\":" + String(bassEnergy) + "}";
  ws.textAll(status);
}

void setup() {
  // Initialize relays
  for (int i = 0; i < 10; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Off
  }
  pinMode(audioPin, INPUT);
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected. IP: " + WiFi.localIP().toString());

  // Initialize WebSocket and server
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
}

void loop() {
  ws.cleanupClients();
  switch (currentPattern) {
    case OFF:
      allOff();
      break;
    case ALL_ON:
      allOn();
      break;
    case CHASE:
      chasePattern();
      break;
    case AUDIO_REACTIVE:
      audioReactive();
      break;
  }
  sendStatus();
  delay(50); // Update rate
}
```
### Code Explanation
- **Wi-Fi**: Connects to the local network using provided credentials.
- **WebSocket**: Hosts a WebSocket server at `/ws` to receive commands (e.g., “off”, “all_on”) and send status (current pattern, bass energy).
- **Audio Processing**:
  - Samples audio at 10kHz, performs FFT to extract bass energy (0–200 Hz).
  - Maps bass energy to the number of active rows (0–10).
- **Patterns**: Supports off, all on, chase, and audio-reactive modes.
- **Status**: Sends JSON updates to the React app every 50ms.

### Setup Instructions
1. Install libraries: `ESPAsyncWebServer`, `AsyncTCP`, `arduinoFFT`.
2. Update `ssid` and `password` with your Wi-Fi credentials.
3. Upload the code to the ESP32 using Arduino IDE or PlatformIO.
4. Open the Serial Monitor (115200 baud) to note the ESP32’s IP address.

## Step 3: Create the React App
The React app will:
- Connect to the ESP32’s WebSocket server.
- Provide buttons to select patterns (Off, All On, Chase, Audio Reactive).
- Display the current pattern and bass energy level.
- Use Tailwind CSS for styling.

### React App Code
Below is a single-page React app hosted in an HTML file, using CDN-hosted React and Tailwind CSS.

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Lighting Control</title>
  <script src="https://cdn.jsdelivr.net/npm/react@18.2.0/umd/react.development.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/react-dom@18.2.0/umd/react-dom.development.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/babel-standalone@7.22.10/babel.min.js"></script>
  <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-100 flex items-center justify-center h-screen">
  <div id="root"></div>
  <script type="text/babel">
    const { useState, useEffect } = React;

    function App() {
      const [pattern, setPattern] = useState('OFF');
      const [bassEnergy, setBassEnergy] = useState(0);
      const [ws, setWs] = useState(null);

      useEffect(() => {
        // Connect to ESP32 WebSocket
        const websocket = new WebSocket('ws://ESP32_IP_ADDRESS/ws'); // Replace with ESP32 IP
        setWs(websocket);

        websocket.onmessage = (event) => {
          const data = JSON.parse(event.data);
          setPattern(data.pattern);
          setBassEnergy(data.bassEnergy);
        };

        websocket.onclose = () => console.log('WebSocket disconnected');
        websocket.onerror = (error) => console.error('WebSocket error:', error);

        return () => websocket.close();
      }, []);

      const sendCommand = (command) => {
        if (ws && ws.readyState === WebSocket.OPEN) {
          ws.send(command);
        }
      };

      return (
        <div className="bg-white p-6 rounded-lg shadow-lg w-full max-w-md">
          <h1 className="text-2xl font-bold mb-4 text-center">Lighting Control</h1>
          <div className="grid grid-cols-2 gap-4 mb-4">
            <button
              className="bg-red-500 text-white py-2 rounded hover:bg-red-600"
              onClick={() => sendCommand('off')}
            >
              Off
            </button>
            <button
              className="bg-green-500 text-white py-2 rounded hover:bg-green-600"
              onClick={() => sendCommand('all_on')}
            >
              All On
            </button>
            <button
              className="bg-blue-500 text-white py-2 rounded hover:bg-blue-600"
              onClick={() => sendCommand('chase')}
            >
              Chase
            </button>
            <button
              className="bg-purple-500 text-white py-2 rounded hover:bg-purple-600"
              onClick={() => sendCommand('audio_reactive')}
            >
              Audio Reactive
            </button>
          </div>
          <div className="text-center">
            <p className="text-lg">Current Pattern: <span className="font-semibold">{pattern}</span></p>
            <p className="text-lg">Bass Energy: <span className="font-semibold">{bassEnergy.toFixed(2)}</span></p>
          </div>
        </div>
      );
    }

    ReactDOM.render(<App />, document.getElementById('root'));
  </script>
</body>
</html>
```

### React App Explanation
- **Dependencies**: Uses CDN-hosted React, ReactDOM, Babel, and Tailwind CSS.
- **WebSocket**: Connects to the ESP32’s WebSocket server (replace `ESP32_IP_ADDRESS` with the IP from the Serial Monitor).
- **UI**:
  - Four buttons to send commands: “off”, “all_on”, “chase”, “audio_reactive”.
  - Displays the current pattern and bass energy received via WebSocket.
- **Styling**: Tailwind CSS for a clean, responsive design.
- **Operation**: Runs in any browser, no build step required.

### Setup Instructions
1. Save the `index.html` file to a local folder.
2. Replace `ESP32_IP_ADDRESS` in the WebSocket URL with the ESP32’s IP address.
3. Serve the file:
   - Option 1: Use a local server (e.g., `python -m http.server 8000`).
   - Option 2: Open directly in a browser (WebSocket will work if the ESP32 is accessible).
4. Access the app at `http://localhost:8000` or the file path.

## Step 4: Test the System
1. **Hardware**:
   - Connect the line-in audio cable to the ESP32 via the voltage divider.
   - Verify the audio signal is 0–3.3V using a multimeter or Serial Monitor.
2. **ESP32**:
   - Upload the firmware and confirm Wi-Fi connection via Serial Monitor.
   - Test patterns using the Serial Monitor or a WebSocket client.
3. **React App**:
   - Open the app in a browser on the same network.
   - Click buttons to change patterns and verify the ESP32 responds.
   - Check that the bass energy updates in audio-reactive mode.
4. **Music Sync**:
   - Play music through the line-in source.
   - Adjust the `map` function in `audioReactive` (e.g., bass energy range) to fine-tune responsiveness.
5. **Full System**:
   - Run the system with all bulbs connected.
   - Ensure relays switch correctly and patterns sync with music.

## Step 5: Deploy at the Event
- **Network**: Ensure the ESP32 connects to a stable local Wi-Fi network.
- **Access**: Share the React app URL or host it on a local server accessible to event staff.
- **Backup**: Have a spare ESP32, audio cable, and power supply.
- **Monitoring**: Use a laptop or tablet to monitor the React app during the event.

## Troubleshooting
- **WebSocket Failure**: Verify the ESP32 IP and network connectivity. Check firewall settings.
- **Audio Sync Issues**: Adjust FFT parameters or use a simple amplitude-based approach if FFT is too complex.
- **Relay Issues**: Ensure GPIO pins are correctly assigned and relays are active-low.
- **Safety**: Double-check AC wiring and insulation before powering on.

## Enhancements
- **Advanced Audio**: Use multiple ADC pins for stereo input or map different frequencies to rows.
- **App Features**: Add sliders for sensitivity or custom pattern sequences.
- **Security**: Add authentication to the WebSocket server for public networks.

</xaiArtifact>

### Next Steps
- **Hardware**: Assemble the line-in circuit and test with a low-volume audio source.
- **ESP32**: Upload the firmware, note the IP, and test WebSocket communication.
- **React App**: Host the app and verify control from a phone or laptop.
- **Tuning**: Adjust audio thresholds during testing to match your music.

Let me know if you need help with specific parts, like tweaking the FFT or adding app features, Cryo! Stay safe with the wiring, and let’s light up that event, Brock-style! 😎