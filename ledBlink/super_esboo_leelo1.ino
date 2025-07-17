const int buttonPin = 2;   // The digital pin connected to the pushbutton
const int ledPin = 13;     // The digital pin connected to the LED

int buttonState = 0;       // Variable to store the current state of the button
bool blinking = false;     // Flag to track if LED should be blinking

unsigned long previousMillis = 0; // Will store last time LED was updated
const long interval = 500;        // Interval at which to blink (milliseconds)

void setup() {
  pinMode(ledPin, OUTPUT);      // Set the LED pin as an output
  pinMode(buttonPin, INPUT);    // Set the button pin as an input
  Serial.begin(9600);           // Initialize serial communication for debugging
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // Check if the button is pressed (LOW because of pull-up if you use INPUT_PULLUP,
  // or HIGH if using pull-down as in the diagram with external resistor)
  // For the pull-down configuration shown, the button will be HIGH when pressed.
  if (buttonState == HIGH) {
    // Small delay to debounce the button (optional but recommended)
    delay(50);
    // Read again to confirm (basic debouncing)
    if (digitalRead(buttonPin) == HIGH) {
      blinking = !blinking; // Toggle the blinking state
      // Wait for the button to be released to avoid multiple toggles from a single press
      while(digitalRead(buttonPin) == HIGH);
    }
  }

  if (blinking) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      // Save the last time you blinked the LED
      previousMillis = currentMillis;

      // If the LED is off, turn it on, and vice-versa:
      if (digitalRead(ledPin) == LOW) {
        digitalWrite(ledPin, HIGH); // Turn LED on
      } else {
        digitalWrite(ledPin, LOW);  // Turn LED off
      }
    }
  } else {
    digitalWrite(ledPin, LOW); // Ensure LED is off when not blinking
  }
}