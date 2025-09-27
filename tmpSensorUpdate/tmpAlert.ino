const int tempPin = A0;     // TMP36 connected to A0
const int ledPin = 13;       // LED connected to pin 13
const int buzzerPin = 8;    // Buzzer connected to pin 8
float threshold = 30.0;     // Default temperature threshold
bool thresholdSet = false;  // Flag to check if threshold is set

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Please enter your targeted temperature (e.g., 30.5): ");
}

void loop() {
  // Check for serial input to set threshold
  if (!thresholdSet && Serial.available() > 0) {
    String input = Serial.readString();  // Read the entire input string
    input.trim();  // Remove any extra spaces or newlines
    
    // Convert string to float
    threshold = input.toFloat();
    
    Serial.print("Threshold set to: ");
    Serial.print(threshold);
    Serial.println("°C");
    thresholdSet = true;
  }

  // Read temperature from TMP36
  int analogValue = analogRead(tempPin);
  float voltage = analogValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C | Threshold: ");
  Serial.print(threshold);
  Serial.println("°C");

  // Check if temperature is above threshold
  if (temperature > threshold) {
    digitalWrite(ledPin, HIGH);    // Turn LED ON
    digitalWrite(buzzerPin, HIGH); // Turn Buzzer ON
    Serial.println("ALERT! Temperature is HIGH!");
    delay(2000);                   // Buzzer ON for 2 seconds
    digitalWrite(buzzerPin, LOW);  // Turn Buzzer OFF
    delay(6000);                   // LED stays ON for total 8 seconds
  } 
  else {
    digitalWrite(ledPin, LOW);     // Turn LED OFF
    digitalWrite(buzzerPin, LOW);  // Ensure Buzzer is OFF
    Serial.println("Temperature is normal");
    delay(2000);                   // Check every 2 seconds
  }

  // Allow changing threshold during operation
  if (Serial.available() > 0) {
    String newInput = Serial.readString();
    newInput.trim();
    float newThreshold = newInput.toFloat();
    
    if (newThreshold > 0) {  // Basic validation
      threshold = newThreshold;
      Serial.print("New threshold set to: ");
      Serial.print(threshold);
      Serial.println("°C");
    }
    // Clear any remaining serial data
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}