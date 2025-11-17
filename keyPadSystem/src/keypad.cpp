#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};  // R1, R2, R3, R4
byte colPins[COLS] = {9, 8, 7, 6};  // C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Keypad Test Started ===");
  Serial.println("Press any key on the keypad...");
  
  //Initialize lcd
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Keypad Test");
  lcd.setCursor(0, 1);  // Set cursor to first column, second row
  lcd.print("Press any key...");

}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);

    // Update LCD display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Key pressed:");
    lcd.setCursor(0, 1);
    lcd.print(key);
    
    // Visual feedback in serial
    Serial.println("----------");
  }
  
  delay(50); // Small delay for stability
}