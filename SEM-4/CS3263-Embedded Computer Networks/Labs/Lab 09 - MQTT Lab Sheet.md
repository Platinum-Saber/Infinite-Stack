---
tags: 
Created: 2025-05-27 16:30
About: 
Reviewed: false
Completion: 0
---
**Name:** Waduge. S.S
**Index**: 220673K
## Learning Outcomes  
At the end of this lab, you will be able to:  
- Understand the operation mode of a messaging protocol considering the publish/subscribe model.  
- Implement MQTT protocol using ESP32 by creating a simple Publisher-Subscriber communication model.  

## Introduction  
MQTT is a lightweight messaging protocol widely used for IoT applications, based on a publish-subscribe model in which “things” and “applications” communicate by publishing and subscribing to topics through an MQTT broker.  
It works on a publish-subscribe model where:  
- **Publisher**: Sends messages to a topic.  
- **Subscriber**: Listens to that topic and receives messages.  

## Lab Tasks  
- Upload the code to two ESP32s: one as publisher, one as subscriber.  
- Modify the topic and observe what happens.  
- Add an LED to the subscriber and toggle it based on message content.  

**What You Will Need for This Lab**  
- 2 × ESP32 Dev Boards  
- 2 × USB Serial Cables  
- Wi-Fi connection  
- Laptop with Arduino IDE  

**MQTT Broker Setup**  
You can use a free MQTT broker:  
- **Broker**: broker.hivemq.com  
- **Port**: 1883  
- **Test Topic**: esp32/test  

**Circuit Diagram**  
You'll just need two ESP32s connected to two laptops separately using USB cables.  

## Method  
**Step 1: Install Required Libraries**  
In Arduino IDE:  
- Go to Sketch > Include Library > Manage Libraries  
- Search and install:  
  - **PubSubClient** by Nick O'Leary  
  - **WiFi library** (already installed)  

**Step 2: Upload the Code to ESP32s**  
Upload the below code to ESP32s separately using the Arduino platform.  

#### Publisher Code  
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32Publisher")) {
      delay(500);
    }
  }
  static int counter = 0;
  String msg = "Hello from ESP32! Count: " + String(counter++);
  client.publish("esp32/test", msg.c_str());
  Serial.println("Published: " + msg);
  delay(2000);
}
```

#### Subscriber Code  
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message received: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
}

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Subscriber")) {
      client.subscribe("esp32/test");
    } else {
      delay(500);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
```

## Observations  
- Open Serial Monitors of both ESP32s.  
- The Publisher will send a message every 2 seconds.  
- The Subscriber will print the received message.  

> [!image] Publisher
> ![[WhatsApp Image 2025-05-27 at 16.55.24_72c873bd.jpg|600]]

> [!image] Subscriber
> ![[WhatsApp Image 2025-05-27 at 16.52.37_4d82fa5b.jpg|600]]

# MQTT Lab Questions and Answers

## Questions and Answers

1. **What is the publish-subscribe model in MQTT, and how does it differ from a client-server model?**  
   **Answer**: The publish-subscribe model in MQTT involves publishers sending messages to topics managed by a broker, which forwards them to subscribers of those topics. This decouples publishers and subscribers, as they don't need to know each other's details. In contrast, a client-server model requires direct communication between client and server, with the server handling requests and responses, making it less scalable for IoT scenarios.

2. **Why is MQTT considered lightweight for IoT applications?**  
   **Answer**: MQTT is lightweight because it uses a simple binary protocol with minimal overhead, designed for low-bandwidth, high-latency, or unreliable networks. It minimizes data packet size and processing requirements, making it ideal for resource-constrained IoT devices like ESP32.

3. **What role does the `callback` function play in the subscriber code?**  
   **Answer**: The `callback` function is triggered whenever a message is received on a subscribed topic. It processes the incoming message, allowing the subscriber to handle or display the data, such as printing it to the Serial Monitor in this lab.

4. **How does the ESP32 maintain a persistent connection to the MQTT broker in the provided code?**  
   **Answer**: The ESP32 checks the connection status using `client.connected()` in the `loop()` function. If disconnected, it calls `reconnect()` to re-establish the connection and resubscribe to the topic, ensuring continuous communication with the broker.

5. **What happens if the Wi-Fi credentials in the code are incorrect?**  
   **Answer**: If the Wi-Fi credentials (SSID or password) are incorrect, the ESP32 will fail to connect to the Wi-Fi network, causing `WiFi.status() != WL_CONNECTED` to loop indefinitely. The Serial Monitor may show repeated connection attempts, and no MQTT communication will occur.

6. **How can you modify the publisher code to send a different message format?**  
   **Answer**: To change the message format, modify the `msg` string in the publisher's `loop()` function. For example, change `String msg = "Hello from ESP32! Count: " + String(counter++);` to `String msg = "Sensor value: " + String( counter++);` to simulate a sensor reading.

7. **What is the significance of the `delay(2000)` in the publisher code?**  
   **Answer**: The `delay(2000)` causes the publisher to send a message every 2 seconds. This prevents overwhelming the broker or network with frequent messages and allows the subscriber sufficient time to process incoming data.

8. **How would you modify the subscriber code to subscribe to multiple topics?**  
   **Answer**: Add additional `client.subscribe("new/topic")` calls in the `reconnect()` function. For example: `client.subscribe("esp32/test2");`. Ensure the `callback` function checks the `topic` parameter to handle messages from different topics appropriately.

9. **What is the purpose of the `client.setServer()` function in both codes?**  
   **Answer**: The `client.setServer(mqtt_server, 1883)` function configures the MQTT client to connect to the specified broker (e.g., `broker.hivemq.com`) and port (1883). It establishes the communication endpoint for publishing or subscribing to topics.

10. **What would happen if the MQTT broker (e.g., broker.hivemq.com) is unreachable?**  
    **Answer**: If the broker is unreachable, the `client.connect()` function will fail, causing the ESP32 to enter a loop of reconnection attempts in the `reconnect()` function (subscriber) or the `loop()` function (publisher). No messages will be sent or received, and the Serial Monitor may show repeated connection failure messages.







