// Motor control pins for L293D
const int leftMotorPin1 = 5;   // IN1 - Controls left motors direction
const int leftMotorPin2 = 6;   // IN2 - Controls left motors direction
const int rightMotorPin1 = 9;  // IN3 - Controls right motors direction
const int rightMotorPin2 = 10; // IN4 - Controls right motors direction

// Motor speed (PWM values 0-255)
int motorSpeed = 200; // Adjust this value for speed control

void setup() {
  // Initialize motor control pins as outputs
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  // Stop all motors initially
  stopMotors();
  
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("=== 4-MOTOR CAR CONTROL ===");
  Serial.println("1: Forward");
  Serial.println("2: Backward");
  Serial.println("3: Left Turn");
  Serial.println("4: Right Turn");
  Serial.println("0: Stop");
  Serial.println("+: Increase Speed");
  Serial.println("-: Decrease Speed");
  Serial.println("s: Current Speed");
  Serial.println("========================");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Execute command based on serial input
    switch(command) {
      case '1': // Forward - all motors forward
        moveForward();
        Serial.println("Moving FORWARD");
        break;
        
      case '2': // Backward - all motors backward
        moveBackward();
        Serial.println("Moving BACKWARD");
        break;
        
      case '3': // Left - right motors forward, left motors backward
        turnLeft();
        Serial.println("Turning LEFT");
        break;
        
      case '4': // Right - left motors forward, right motors backward
        turnRight();
        Serial.println("Turning RIGHT");
        break;
        
      case '0': // Stop - all motors off
      case ' ':
        stopMotors();
        Serial.println("STOPPED");
        break;
        
      case '+': // Increase speed
        motorSpeed = min(255, motorSpeed + 20);
        Serial.print("Speed increased to: ");
        Serial.println(motorSpeed);
        break;
        
      case '-': // Decrease speed
        motorSpeed = max(0, motorSpeed - 20);
        Serial.print("Speed decreased to: ");
        Serial.println(motorSpeed);
        break;
        
      case 's': // Show current speed
        Serial.print("Current speed: ");
        Serial.println(motorSpeed);
        break;
        
      case 't': // Test all motors
        testMotors();
        break;
        
      default:
        Serial.println("Invalid command! Use: 1,2,3,4,0,+,-,s,t");
        break;
    }
  }
}

void moveForward() {
  // Left motors forward
  analogWrite(leftMotorPin1, motorSpeed);
  digitalWrite(leftMotorPin2, LOW);
  
  // Right motors forward
  analogWrite(rightMotorPin1, motorSpeed);
  digitalWrite(rightMotorPin2, LOW);
}

void moveBackward() {
  // Left motors backward
  digitalWrite(leftMotorPin1, LOW);
  analogWrite(leftMotorPin2, motorSpeed);
  
  // Right motors backward
  digitalWrite(rightMotorPin1, LOW);
  analogWrite(rightMotorPin2, motorSpeed);
}

void turnLeft() {
  // Left motors backward (makes sharp left turn)
  digitalWrite(leftMotorPin1, LOW);
  analogWrite(leftMotorPin2, motorSpeed);
  
  // Right motors forward
  analogWrite(rightMotorPin1, motorSpeed);
  digitalWrite(rightMotorPin2, LOW);
}

void turnRight() {
  // Left motors forward
  analogWrite(leftMotorPin1, motorSpeed);
  digitalWrite(leftMotorPin2, LOW);
  
  // Right motors backward (makes sharp right turn)
  digitalWrite(rightMotorPin1, LOW);
  analogWrite(rightMotorPin2, motorSpeed);
}

void stopMotors() {
  // Stop all motors
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void testMotors() {
  Serial.println("Testing LEFT motors...");
  analogWrite(leftMotorPin1, motorSpeed);
  digitalWrite(leftMotorPin2, LOW);
  delay(1000);
  stopMotors();
  delay(500);
  
  Serial.println("Testing RIGHT motors...");
  analogWrite(rightMotorPin1, motorSpeed);
  digitalWrite(rightMotorPin2, LOW);
  delay(1000);
  stopMotors();
  delay(500);
  
  Serial.println("Test completed!");
}