// Define segment pins
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // a, b, c, d, e, f, g

// Define button pins
const int incButtonPin = 9;
const int decButtonPin = 10;

// 7-segment patterns for digits 0-9 (common anode)
const byte digitPatterns[10] = {
  B0000001, // 0 - segments: a,b,c,d,e,f
  B1001111, // 1 - segments: b,c
  B0010010, // 2 - segments: a,b,d,e,g
  B0000110, // 3 - segments: a,b,c,d,g
  B1001100, // 4 - segments: b,c,f,g
  B0100100, // 5 - segments: a,c,d,f,g
  B0100000, // 6 - segments: a,c,d,e,f,g
  B0001111, // 7 - segments: a,b,c
  B0000000, // 8 - all segments
  B0000100  // 9 - segments: a,b,c,d,f,g
};

int currentNumber = 0;
int lastIncButtonState = HIGH;
int lastDecButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  // Initialize segment pins as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // Initialize button pins with INPUT_PULLUP
  pinMode(incButtonPin, INPUT_PULLUP);
  pinMode(decButtonPin, INPUT_PULLUP);
  
  // Display initial number
  displayNumber(currentNumber);
  
  Serial.begin(9600); // For debugging
}

void loop() {
  int incReading = digitalRead(incButtonPin);
  int decReading = digitalRead(decButtonPin);
  
  // Increment button pressed (goes LOW with INPUT_PULLUP)
  if (incReading == LOW && lastIncButtonState == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      currentNumber++;
      if (currentNumber > 9) currentNumber = 0;
      displayNumber(currentNumber);
      Serial.print("Incremented to: ");
      Serial.println(currentNumber);
    }
    lastDebounceTime = millis();
  }
  
  // Decrement button pressed (goes LOW with INPUT_PULLUP)
  if (decReading == LOW && lastDecButtonState == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      currentNumber--;
      if (currentNumber < 0) currentNumber = 9;
      displayNumber(currentNumber);
      Serial.print("Decremented to: ");
      Serial.println(currentNumber);
    }
    lastDebounceTime = millis();
  }
  
  lastIncButtonState = incReading;
  lastDecButtonState = decReading;
}

void displayNumber(int number) {
  number = constrain(number, 0, 9);
  byte pattern = digitPatterns[number];
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (pattern & (1 << (6-i))) ? HIGH : LOW);
  }
}