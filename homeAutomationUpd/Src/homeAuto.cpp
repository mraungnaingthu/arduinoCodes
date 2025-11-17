#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Function Delearations
void readSensors();
void checkButtons();
void setRGBColor(int red, int green, int blue);
void soundAlarm();

// Pin definitions - CORRECTED FOR YOUR HARDWARE
const int dhtPin = 2;          // DHT22 connected to pin 2
const int gasSensor = A0;      // Gas sensor connected to A0
const int motionDetector = 3;  // PIR sensor connected to pin 3
const int button1 = 6;         // Button 1 connected to pin 6
const int button2 = 7;         // Button 2 connected to pin 7
const int button3 = 8;         // Button 3 connected to pin 8
const int button4 = 9;         // Button 4 connected to pin 9
const int redPin = A1;         // RGB Red connected to A1
const int greenPin = 4;        // RGB Green connected to pin 4
const int bluePin = 5;         // RGB Blue connected to pin 5
const int servoPin = A2;       // Servo connected to A2
const int buzzer = A3;         // Buzzer connected to A3
const int relay1 = 13;         // Relay 1 connected to pin 13
const int relay2 = 12;         // Relay 2 connected to pin 12
const int relay3 = 11;         // Relay 3 connected to pin 11
const int relay4 = 10;         // Relay 4 connected to pin 10

// Initialize components
#define DHT_TYPE DHT22
DHT dht(dhtPin, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

// Variables
int servoPosition = 0;
bool alarmActive = false;
int relay1State = LOW;
int relay2State = LOW;
int relay3State = LOW;
int relay4State = LOW;

void setup() {
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(gasSensor, INPUT);
  pinMode(motionDetector, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  // Initialize components
  dht.begin();
  lcd.init();
  lcd.backlight();
  myServo.attach(servoPin);
  
  // Initial states
  setRGBColor(0, 0, 0);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  
  Serial.println("Home Automation System Started");
  lcd.print("System Ready");
  delay(2000);

  readSensors();
}

void loop() {
  checkButtons();
  delay(1000);
}

void readSensors() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Read gas sensor
  int gasValue = analogRead(gasSensor);
  
  // Read motion sensor
  int motion = digitalRead(motionDetector);
  
  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT Sensor Error!");
    lcd.clear();
    lcd.print("Sensor Error!");
    return;
  }
  
  // Display on Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Gas: ");
  Serial.print(gasValue);
  Serial.print(", Motion: ");
  Serial.println(motion);
  
  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("G:");
  lcd.print(gasValue);
  lcd.print(" M:");
  lcd.print(motion);
  
  // Gas alarm
  if (gasValue > 300) { // Adjust threshold as needed
    soundAlarm();
    setRGBColor(255, 0, 0); // Red for danger
  }
}

void checkButtons() {
  // Button 1 - Control RGB LED
  if (digitalRead(button1) == LOW) {
    Serial.println("Button 1 Pressed: RGB LED Green");
    setRGBColor(0, 255, 0); // Green
    delay(300); // Debounce
  }
  
  // Button 2 - Control Servo
  if (digitalRead(button2) == LOW) {
    Serial.println("Button 2 Pressed: Move Servo");
    lcd.clear();
    lcd.print("Moving Servo");
    setRGBColor(0, 0, 255); // Blue
    delay(300); // Debounce
    servoPosition = (servoPosition + 45) % 180;
    myServo.write(servoPosition);
    Serial.println("Servo Position: " + String(servoPosition));
    Serial.println("Servo moved to " + String(servoPosition) + " degrees");
    delay(300); // Debounce
  }
  
  // Button 3 - Control Relay 1 & 2
  if (digitalRead(button3) == LOW) {
    Serial.println("Button 3 Pressed: Toggle Relays 1 & 2");
    lcd.clear();
    lcd.print("Toggling Relays 1&2");
    relay1State = !relay1State;
    relay2State = !relay2State;
    digitalWrite(relay1, relay1State);
    digitalWrite(relay2, relay2State);
    Serial.print("Relay 1 & 2: ");
    Serial.println(relay1State ? "ON" : "OFF");
    delay(300); // Debounce
  }
  
  // Button 4 - Control Relay 3 & 4
  if (digitalRead(button4) == LOW) {
    Serial.println("Button 4 Pressed: Toggle Relays 3 & 4");
    lcd.clear();
    lcd.print("Toggling Relays 3&4");
    relay3State = !relay3State;
    relay4State = !relay4State;
    digitalWrite(relay3, relay3State);
    digitalWrite(relay4, relay4State);
    Serial.print("Relay 3 & 4: ");
    Serial.println(relay3State ? "ON" : "OFF");
    delay(300); // Debounce
  }
}

void setRGBColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void soundAlarm() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
}