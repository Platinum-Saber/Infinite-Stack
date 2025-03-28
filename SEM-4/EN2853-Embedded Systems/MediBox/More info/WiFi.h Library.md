---
tags:
  - EmbeddedSystems
  - ESP32
Created: 2025-03-27 13:17
About: 
Reviewed: false
Completion: 0
---

## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```



## Overview


> [!info] <WiFi.h>
> The `WiFi.h` library is an official Arduino library designed for ESP32 and ESP8266 microcontrollers to enable Wi-Fi functionality. It provides a simple interface for connecting to Wi-Fi networks, managing connections, and performing network-related tasks.



## Key Features


> [!tip] Wi-Fi Modes
>     
> - The library supports multiple Wi-Fi modes:
> 	- `WIFI_STA`: Station mode (connects to an existing Wi-Fi network).
> 	- `WIFI_AP`: Access Point mode (creates a Wi-Fi network for other devices to connect).
> 	- `WIFI_AP_STA`: Dual mode (acts as both a station and an access point).

> [!info] Connecting to Wi-Fi
>     
> - The `WiFi.begin(ssid, password)` function is used to connect to a Wi-Fi network.
> - Additional parameters like channel and BSSID can be specified for advanced configurations. `WiFi.begin(ssid, password, channel)`
> >[!NOTE]- Why select a channel
> > By default, `WiFi.begin(ssid, password)` scans all available channels to find the specified network. However, if you know the exact channel of the Wi-Fi network you want to connect to, you can pass it as the third parameter. 
> > This can:
> > 1. **Speed up the connection process** by skipping the channel scan.
> > 2. **duce interference** if you are working in a controlled environment with multiple Wi-Fi networks.

> [!warning] Connection Status
>     
> - The `WiFi.status()` function returns the current connection status, such as:
> 	- `WL_CONNECTED`: Successfully connected to a Wi-Fi network.
> 	- `WL_DISCONNECTED`: Not connected to any network.
> 	- Other statuses like `WL_IDLE_STATUS`, `WL_NO_SSID_AVAIL`, etc.

> [!info] IP Address Management
>     
> - The library provides functions to retrieve the device's IP address:
> 	- `WiFi.localIP()`: Returns the local IP address assigned to the ESP32.
> 	- `WiFi.gatewayIP()`: Returns the gateway IP address.

> [!info] Signal Strength
>     
> - The `WiFi.RSSI()` function returns the Received Signal Strength Indicator (RSSI) of the connected network, measured in dBm.

> [!check] Access Point Configuration
> 
> - The library allows the ESP32 to act as an access point using `WiFi.softAP(ssid, password)`.
> - Additional configurations like channel and maximum connections can also be set.

> [!info] Event Handling
>     
> - The library supports event handling for Wi-Fi events such as connection, disconnection, and IP address changes.

> [!example] Advanced Features
>     
> - Functions for scanning available networks (`WiFi.scanNetworks()`).
> - Support for static IP configuration.
> - Functions for disconnecting from a network (`WiFi.disconnect()`).

## Sample Codes

### 1. Creating a Wi-Fi Access Point

```cpp
#include <WiFi.h>
void setup()
{
    Serial.begin(115200);

    WiFi.softAP("ESP32_AP", "password123");
    Serial.println("Access Point Started");
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
}
```

### 2. Connecting to a Wi-Fi Network

```cpp
#include <WiFi.h>
const char *ssid = "Your_SSID";
const char *password = "Your_PASSWORD";

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
```

### 3. Getting The Wi-Fi IP

```cpp
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway IP: ");
    Serial.println(WiFi.gatewayIP());
```

### 4. Setting Wi-Fi Mode

```cpp
#include <WiFi.h>
void setup()
{
    Serial.begin(115200);

    // Station mode (connect to an existing Wi-Fi network)
    WiFi.mode(WIFI_STA);
    Serial.println("Wi-Fi set to Station mode");

    // Access Point mode (create a Wi-Fi network)
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32_AP", "password123");
    Serial.println("Wi-Fi set to Access Point mode");

    // Dual mode (Station + Access Point)
    WiFi.mode(WIFI_AP_STA);
    Serial.println("Wi-Fi set to Dual mode");
}
```

### 5. Wi-Fi RSSI

```cpp
#include <WiFi.h>
void setup()
{
    Serial.begin(115200);
    WiFi.begin("Your_SSID", "Your_PASSWORD");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
}
void loop()
{
    long rssi = WiFi.RSSI();
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");
    delay(2000);
}
```

### 6. Wi-Fi Events

```cpp
#include "wifi_manager.h"
#include "display.h"
#include <WiFi.h>

const char *ssid = "Wokwi-Guest";
const char *password = "";

void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_CONNECTED:
        Serial.println("Wi-Fi Connected");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("Wi-Fi Disconnected");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        break;
    default:
        break;
    }
}

void init_wifi()
{
    WiFi.onEvent(WiFiEvent);
    WiFi.begin(ssid, password, 6);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        clear_display();
        print_line("Connecting to WIFI", 0, 0, 2);
        delay(250);
    }
    clear_display();
    print_line("Connected to WIFI", 0, 0, 2);
    delay(1000);
}
```
