int driverPin1 = 9;
int driverPin2 = 6;
char input = '0';  // Initialize with a safe value

void setup()
{
  pinMode(driverPin1, OUTPUT);
  pinMode(driverPin2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter 1 to run motor clockwise: ");
  Serial.println("Enter 2 to run motor counterClockwise: ");
  Serial.println("Enter 0 to stop motor: ");
  digitalWrite(driverPin1, LOW);  // Ensure motor starts OFF
  digitalWrite(driverPin2, LOW);
}

void loop()
{
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.print("the value is: ");
    Serial.println(input);
    
    // Turn both pins OFF first to prevent short circuits
    digitalWrite(driverPin1, LOW);
    digitalWrite(driverPin2, LOW);
    
    // Only check input immediately after receiving it
    if (input == '1') {
      digitalWrite(driverPin1, HIGH);
      Serial.println("Motor ON clockwise");
    } else if (input == '2') {
      digitalWrite(driverPin2, HIGH);
      Serial.println("Motor ON CounterClockWise");
    } else if (input == '0') {
      Serial.println("Motor OFF");
    } else {
      Serial.println("Invalid input! Use 0, 1, or 2");
    }
  }
  
  // Optional: Add a small delay to reduce loop speed
  delay(100);
}