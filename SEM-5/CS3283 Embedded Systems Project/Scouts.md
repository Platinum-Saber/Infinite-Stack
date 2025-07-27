
##  1. ESP32 connects to Raspberry Pi Wi-Fi Access Point (`ScoutNet`)

### ESP32 Arduino Code: Wi-Fi + UDP Setup

- Connects the ESP32 to the Pi-hosted `ScoutNet`
- Sends dummy LiDAR scan data over UDP to the Pi (acting as coordinator)
    

```cpp
#include <WiFi.h>
#include <WiFiUdp.h>

// Replace with your Pi's AP credentials
const char* ssid = "ScoutNet";
const char* password = "terrainmap123";

const char* coordinator_ip = "10.42.0.1"; // Pi's static IP
const int coordinator_port = 5005;          // UDP port

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  
  // Connect to Pi AP
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ScoutNet");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Pi Access Point.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  udp.begin(coordinator_port); // not strictly required to bind here
}

void loop() {
  // Example payload (replace with real LiDAR/odometry later)
  String payload = "{\"id\":1,\"angle\":90,\"range\":1.23}";

  udp.beginPacket(coordinator_ip, coordinator_port);
  udp.print(payload);  // Send JSON payload
  udp.endPacket();

  delay(100);  // 10Hz simulation
}
```

---

## 2. Pi Receives UDP Packets (Coordinator Setup Preview)

Quick test (not ROS yet) to run on the Raspberry Pi to check if it's receiving data:

```bash
# Terminal on Raspberry Pi
nc -ul 5005
```

Result:

```
{"id":1,"angle":90,"range":1.23}
```

