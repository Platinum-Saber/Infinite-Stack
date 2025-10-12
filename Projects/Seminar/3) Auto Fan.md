![[Pasted image 20250512213555.png]]
![[Auto Motor.mp4]]

### Code
```cpp
const int MOTOR_PIN = 8;
const int SENSOR_PIN = A0;
int sensorValue = 0;

void setup()
{
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  sensorValue = analogRead(SENSOR_PIN);
  float temp = getTemp(sensorValue);
  Serial.print("Temp: ");
  Serial.println(temp);
  
  if (temp > 30){
	digitalWrite(MOTOR_PIN, HIGH);
  }
  else{digitalWrite(MOTOR_PIN, LOW);}
  
}

float getTemp(int val){
  return (val * 0.49)-49.8;
}
```


> [!tip] [Tinkercad Circuit Link](https://www.tinkercad.com/things/3OnA37SXaJD-3-auto-fan?sharecode=xKCB8sBCblbToEXkqcVdD2JH02vytNhSPOJBIIhzCUc)

