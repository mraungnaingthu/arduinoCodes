int irPin = 7;
int ledPin = 2;

void setup() {
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(irPin) == LOW) {
    digitalWrite(ledPin, HIGH);  // Object detected
  } else {
    digitalWrite(ledPin, LOW);   // No object
  }
}
