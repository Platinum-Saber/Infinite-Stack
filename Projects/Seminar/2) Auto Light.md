> [!video] Demo
> ![[Auto Light.gif]]

> [!image] Simplified Schematic
> ![[Pasted image 20250512195156.png]]

### Code
```cpp
const int LED_PIN = 8;
const int LDR_PIN = A0;
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  int sensorValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(sensorValue);
  if (sensorValue < 150) {digitalWrite(LED_PIN, HIGH);} 
  else {digitalWrite(LED_PIN, LOW);}
}
```
