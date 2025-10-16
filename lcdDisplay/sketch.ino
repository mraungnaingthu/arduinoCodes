#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200

// Initialize I2C LCD (address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int potenPin = A0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool modeSelected = false;
char currentMode = '0';

// Function to get distance from ultrasonic sensor
int getDistance() {
  unsigned int distance = sonar.ping_cm();
  if (distance == 0) {
    return MAX_DISTANCE; // Return max distance if no echo
  }
  return distance;
}

void setup() {
  Serial.begin(9600);
  
  // Initialize I2C LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Wait for serial connection to establish
  while (!Serial) {
    delay(10); // Wait for serial port to connect
  }
  
  // Display mode selection message
  lcd.setCursor(0, 0);
  lcd.print("Choose Sensor:");
  lcd.setCursor(0, 1);
  lcd.print("1:POT 2:SONIC");
  
  Serial.println("=== SENSOR MODE SELECTION ===");
  Serial.println("Send '1' for Potentiometer Mode");
  Serial.println("Send '2' for Ultrasonic Sensor Mode");
  Serial.println("Waiting for input...");
  
  delay(2000); // Show instruction for 2 seconds
}

void loop() {
  // Check serial input for mode selection
  if (Serial.available() > 0) {
    char mode = Serial.read();
    
    // Ignore newline/carriage return characters
    if (mode == '\n' || mode == '\r') {
      return;
    }
    
    Serial.print("Mode selected: ");
    Serial.println(mode);
    
    if (mode == '1') {
      Serial.println("Entering Potentiometer Mode");
      potentiometerMode();
    } else if (mode == '2') {
      Serial.println("Entering Ultrasonic Sensor Mode");
      ultrasonicMode();
    } else {
      Serial.println("Invalid input! Please send '1' or '2'");
    }
  }
  
  // Default: show instruction (only if no mode is active)
  if (!modeSelected) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Serial Monitor:");
    lcd.setCursor(0, 1);
    lcd.print("Send 1 or 2");
    delay(2000);
  }
}

void potentiometerMode() {
  modeSelected = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("POTENTIOMETER");
  
  while (true) {
    int data = analogRead(potenPin);
    int percentage = map(data, 0, 1023, 0, 100);
    
    // Print to Serial Monitor
    Serial.print("Potentiometer: ");
    Serial.print(data);
    Serial.print(" (");
    Serial.print(percentage);
    Serial.println("%)");
    
    // Display on LCD
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(data);
    lcd.print(" ");
    if (data < 1000) lcd.print(" "); // Alignment
    if (data < 100) lcd.print(" ");  // Alignment
    
    lcd.setCursor(12, 1);
    lcd.print(percentage);
    lcd.print("% ");
    
    // Check condition
    lcd.setCursor(0, 0);
    if (data > 500) {
      lcd.print("HIGH >500    ");
    } else {
      lcd.print("LOW <=500    ");
    }
    
    // Check for mode change
    if (Serial.available() > 0) {
      char input = Serial.read();
      if (input == '1' || input == '2') {
        modeSelected = false;
        Serial.println("Exiting Potentiometer Mode");
        return;
      }
    }
    
    delay(500);
  }
}

void ultrasonicMode() {
  modeSelected = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ULTRASONIC SENSOR");
  
  while (true) {
    int distance = getDistance();
    
    // Print to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Display on LCD
    lcd.setCursor(0, 1);
    
    if (distance < 20) {
      lcd.print("Too close!      ");
      lcd.setCursor(10, 1);
      lcd.print(distance);
      lcd.print("cm ");
    } else if (distance < 100) {
      lcd.print("Safe distance   ");
      lcd.setCursor(10, 1);
      lcd.print(distance);
      lcd.print("cm ");
    } else {
      lcd.print("No object       ");
      lcd.setCursor(10, 1);
      lcd.print(distance);
      lcd.print("cm ");
    }
    
    // Check for mode change
    if (Serial.available() > 0) {
      char input = Serial.read();
      if (input == '1' || input == '2') {
        modeSelected = false;
        Serial.println("Exiting Ultrasonic Mode");
        return;
      }
    }
    
    delay(500);
  }
}