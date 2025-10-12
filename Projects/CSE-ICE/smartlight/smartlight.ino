// LD19 -> ESP32 (UART2) -> USB Serial (parsed view)
// Shows header-aligned packets and measurement points.
#include <HardwareSerial.h>

HardwareSerial LIDAR(2);
const int PIN_RX = 16;
const int PIN_TX = 17;

const uint8_t LD19_HEADER = 0x54;
const uint8_t LD19_VERLEN = 0x2C;   // type(1)<<5 | points(12)
const size_t  LD19_FRAME  = 47;

bool readExact(HardwareSerial& s, uint8_t* buf, size_t n, uint32_t to_ms=25) {
  uint32_t t0 = millis(), got = 0;
  while (got < n) {
    int c = s.read();
    if (c >= 0) buf[got++] = (uint8_t)c;
    else {
      if (millis() - t0 > to_ms) return false;
      delayMicroseconds(200);
    }
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("\nLD19 frame viewer...");
  LIDAR.begin(230400, SERIAL_8N1, PIN_RX, PIN_TX, false);
}

void loop() {
  // Seek header 0x54
  int c = LIDAR.read();
  if (c < 0) return;
  if ((uint8_t)c != LD19_HEADER) return;

  uint8_t f[LD19_FRAME];
  f[0] = LD19_HEADER;
  if (!readExact(LIDAR, f + 1, LD19_FRAME - 1)) return;

  // Quick sanity: VerLen must be 0x2C for 12 points
  if (f[1] != LD19_VERLEN) return;

  // Unpack helpers
  auto U16 = [&](int idx)->uint16_t { return (uint16_t)f[idx] | ((uint16_t)f[idx+1] << 8); };

  uint16_t speed_dps    = U16(2);        // degrees per second
  uint16_t start_angle1 = U16(4);        // hundredths of degree
  // points start at byte 6, 12 * (2+1) = 36 bytes
  uint16_t end_angle1   = U16(42);       // hundredths of degree
  uint16_t timestamp_ms = U16(44);
  uint8_t  crc8         = f[46];         // (not checked here)

  Serial.print("\nPacket: spd=");
  Serial.print(speed_dps);
  Serial.print(" dps  start=");
  Serial.print(start_angle1 / 100.0, 2);
  Serial.print("°  end=");
  Serial.print(end_angle1 / 100.0, 2);
  Serial.print("°  ts=");
  Serial.print(timestamp_ms);
  Serial.print(" ms  (crc=0x");
  if (crc8 < 16) Serial.print('0');
  Serial.print(crc8, HEX);
  Serial.println(")");

  // Print the 12 points: distance(mm) + intensity
  int off = 6;
  for (int i = 0; i < 12; ++i) {
    uint16_t dist_mm = (uint16_t)f[off] | ((uint16_t)f[off+1] << 8);
    uint8_t  inten   = f[off+2];
    off += 3;
    Serial.print("  pt");
    if (i < 10) Serial.print('0');
    Serial.print(i);
    Serial.print(": d=");
    Serial.print(dist_mm);
    Serial.print("mm  I=");
    Serial.println(inten);
  }
}
