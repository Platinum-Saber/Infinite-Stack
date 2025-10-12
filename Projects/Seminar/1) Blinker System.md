> [!video] Demo
> ![[Blinker System.gif]]


> [!image] Simplified Schematic
> ![[Pasted image 20250512190144.png]]


### Code
```cpp
const int LED_PIN = 8;
void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(500); 
  digitalWrite(LED_PIN, LOW);
  delay(500); 
}
```
