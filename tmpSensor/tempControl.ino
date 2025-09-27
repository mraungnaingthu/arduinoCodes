int ledPin = 13;
int sensorPin = A0;
int sensorValue = 0;
float temperature = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  temperature = (voltage - 0.5) * 100.0;
  
  Serial.print("Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.println("°C");
  
  if (temperature > 30.0) {  // 30°C threshold
    digitalWrite(ledPin, HIGH);
    delay(8000);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}