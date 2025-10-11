int xPin = A0;
int yPin = A1;

// LED assignments:
const int yellowLed = 5;   //UP
const int greenLed = 3;    //LEFT
const int blueLed = 6;    //Below
const int redLed = 4;      //Right

int buttonPin = 6;

// Define center position (since your joystick shows 512 at rest)
const int CENTER_MIN = 512;
const int CENTER_MAX = 512;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(greenLed, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    int xValue = analogRead(xPin);
    int yValue = analogRead(yPin);
    int buttonState = digitalRead(buttonPin);

    Serial.print("X: ");
    Serial.print(xValue);
    Serial.print(" | Y: ");
    Serial.print(yValue);
    Serial.print(" | Button: ");
    Serial.println(buttonState);

    // Turn off all LEDs first
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(blueLed, LOW);

    // Check if in center position - FIXED with proper comparison
    bool inCenter = (xValue == CENTER_MIN && yValue == CENTER_MAX);

    if (!inCenter) {
        
        if (yValue > CENTER_MIN) {
            
            digitalWrite(redLed, HIGH);
            Serial.println("LEFT - RED LED ON");
        }
        else if (yValue < CENTER_MAX) {
            
            digitalWrite(greenLed, HIGH);
            Serial.println("Right - GREEN LED ON");
        }

        
        if (xValue < CENTER_MIN) {
            
            digitalWrite(blueLed, HIGH);
            Serial.println("Down - BLUE LED ON");
        }
        else if (xValue > CENTER_MAX) {
            // Right position - Green LED
            digitalWrite(yellowLed, HIGH);
            Serial.println("UPPER - YELLOW LED ON");
        }
    }
    else {
        Serial.println("CENTER - All LEDs OFF");
    }

    /*// Optional: Button press could turn on all LEDs
    if (buttonState == LOW) {
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, HIGH);
        digitalWrite(yellowLed, HIGH);
        digitalWrite(blueLed, HIGH);
        Serial.println("BUTTON PRESSED - All LEDs ON");
        delay(500);
    }*/

    delay(100);
}