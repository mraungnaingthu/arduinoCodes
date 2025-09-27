int ledPin = 13;
int input;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter 1 to turn LED on for 8 seconds: ");

}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();

    if (input == '1') {
      Serial.println("LED on for 8 seconds");
      digitalWrite(ledPin, HIGH);
      delay(8000);
      digitalWrite(ledPin, LOW);
      Serial.println("LED off");
      Serial.println("Enter 1 to turn on LED again: ");

    }
    else {
    Serial.println("Enter only 1");
  }
  }
  
  /*while (Serial.available() > 0) {
    Serial.read();
  }*/
  
}