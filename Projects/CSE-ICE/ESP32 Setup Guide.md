
## 🧱 Step 1: Install the Arduino IDE

### 🔗 Download

Go to: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)  
Download the latest version of Arduino IDE (preferably 2.x).

### 💻 Install

- **Windows**: Run `.exe` file and install as administrator
- **macOS**: Drag the app to Applications
- **Linux**: Extract and run `install.sh` from terminal

---

## 🧩 Step 2: Install CP210x/CH340 Drivers (If needed)

ESP32 boards typically use either:

- **CH340** USB-to-Serial chip
- **CP2102** USB-to-Serial chip
### 🔍 Find Your Chip

Look at the chip near the USB port on your ESP32:

- Marked **CH340G** → Install CH340 driver
- Marked **CP2102** → Install CP210x driver

### 💾 Download Drivers

- **CH340**: [https://sparks.gogo.co.nz/ch340.html](https://sparks.gogo.co.nz/ch340.html)
- **CP210x**: [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

### 💡 After installing:

- Reboot your PC
- Plug in the ESP32
- Check if a new COM port appears (in Device Manager → "Ports (COM & LPT)")

---

## 📦 Step 3: Add ESP32 Support to Arduino IDE

### 🛠️ Open Preferences

- **File → Preferences**
- Find **“Additional Board URLs”** field

### ➕ Add ESP32 URL:

```plaintext
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

> If you already have other URLs, separate them with a comma.

---

## 📥 Step 4: Install ESP32 Board Package

- Go to **Tools → Board → Board Manager**
- Search for **"ESP32 by Espressif Systems"**
- Click **Install** (choose the latest version)

✅ This installs support for all common ESP32 boards.

---

## 🧪 Step 5: Select the Correct Board and Port

- **Tools → Board → ESP32 Arduino → [Your Board]**
    - For example: `ESP32 Dev Module`
- **Tools → Port → COMx**
    - Choose the port that appears when ESP32 is plugged in

---

## 🖋️ Step 6: Test with Blink Sketch

### 🔄 File → Examples → 01.Basics → Blink

Replace built-in LED pin if needed:

```cpp
// Change built-in LED pin for ESP32
#define LED_BUILTIN 2  // Onboard LED is usually on GPIO 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // ON
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);   // OFF
  delay(500);
}
```

### 🔼 Upload

- Click the **Upload button**
- Wait for compilation and upload to complete

---

## ⚠️ Troubleshooting

|Issue|Solution|
|---|---|
|Board not detected|Try a different USB cable or port. Install missing driver.|
|Failed to upload|Hold `BOOT` button while uploading on some boards.|
|Permission denied (Linux)|Run `sudo usermod -aG dialout $USER` then reboot.|
|No COM port (macOS)|Try installing the correct driver (especially CP210x).|

---

## 🧪 Optional: Enable Serial Monitor

- Click the **Serial Monitor** (top-right) in IDE
- Set **baud rate** to match your sketch (usually `115200`)
- Add `Serial.begin(115200);` in `setup()` to debug

---

## 🧰 Tools & Resources

- [ESP32 Arduino GitHub](https://github.com/espressif/arduino-esp32)
- [ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [Serial Drivers Guide](https://learn.sparkfun.com/tutorials/how-to-install-ftdi-drivers/all)
