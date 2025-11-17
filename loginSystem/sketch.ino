#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

int keyValue = 0;
char circleRotation = ' ';
int keyTime = 0;
int step = 0;
bool gameCompleted = false;

const int CORRECT_VALUE = 4;
const char CORRECT_ROTATION = 'R';
const int CORRECT_TIME = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void goldenBox(int value, char rotation, int time) {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (value == CORRECT_VALUE && rotation == CORRECT_ROTATION && time == CORRECT_TIME) {
    lcd.print("Box is open! :)");
    lcd.setCursor(0, 1);
    lcd.print("Congratulations!");
    gameCompleted = true;
    
    Serial.println("SUCCESS: Box opened!");
  } else {
    lcd.print("Wrong combination!");
    lcd.setCursor(0, 1);
    lcd.print("Please try again!");
    
    Serial.print("FAILED: ");
    Serial.print(value);
    Serial.print("-");
    Serial.print(rotation);
    Serial.print("-");
    Serial.println(time);
  }
}

void displayStep(int currentStep) {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  switch(currentStep) {
    case 1:
      lcd.print("Step 1: Enter value");
      lcd.setCursor(0, 1);
      lcd.print("Press 1-9: ");
      break;
    case 2:
      lcd.print("Step 2: Rotation");
      lcd.setCursor(0, 1);
      lcd.print("A=Left, B=Right: ");
      break;
    case 3:
      lcd.print("Step 3: Enter time");
      lcd.setCursor(0, 1);
      lcd.print("Press 1-9: ");
      break;
  }
}

void displayWelcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Golden Box Game");
  lcd.setCursor(0, 1);
  lcd.print("Press any key...");
}

void resetGame() {
  keyValue = 0;
  circleRotation = ' ';
  keyTime = 0;
  step = 1;
  gameCompleted = false;
  displayStep(step);
}

void setup() {
  Serial.begin(9600);
  Serial.println("=== Golden Box Game ===");
  Serial.println("Correct combination: 4-R-4");
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  displayWelcome();
  
  // Wait for any key to start
  while(!keypad.getKey()) {
    delay(100);
  }
  
  step = 1;
  displayStep(step);
}

void loop() {
  if (gameCompleted) {
    // Game completed state - wait for reset or additional input
    delay(100);
    return;
  }
  
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    
    switch(step) {
      case 1: // Get value
        if (key >= '1' && key <= '9') {
          keyValue = key - '0';
          lcd.setCursor(10, 1);
          lcd.print(key);
          Serial.print("Value set to: ");
          Serial.println(keyValue);
          step = 2;
          delay(800);
          displayStep(step);
        }
        break;
        
      case 2: // Get rotation
        if (key == 'A' || key == 'B') {
          circleRotation = (key == 'A') ? 'L' : 'R';
          lcd.setCursor(17, 1);
          lcd.print(key);
          Serial.print("Rotation set to: ");
          Serial.println(circleRotation);
          step = 3;
          delay(800);
          displayStep(step);
        }
        break;
        
      case 3: // Get time
        if (key >= '1' && key <= '9') {
          keyTime = key - '0';
          lcd.setCursor(10, 1);
          lcd.print(key);
          Serial.print("Time set to: ");
          Serial.println(keyTime);
          
          // Check combination
          delay(800);
          goldenBox(keyValue, circleRotation, keyTime);
          
          // Reset for next attempt after delay
          delay(3000);
          if (!gameCompleted) {
            resetGame();
          }
        }
        break;
    }
  }
  
  delay(50);
}