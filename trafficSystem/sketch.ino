// Traffic light pins
const int green = 11;
const int yellow = 12;
const int red = 13;

// 7-segment display pins
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;

// Timing variables
const int redTime = 6;      // Red light duration: 9-8-7-6-5-4
const int greenTime = 6;    // Green light duration: 9-8-7-6-5-4
const int yellowTime = 3;   // Yellow light duration: 3-2-1

int currentTime = 9;        // Start counting from 9
int currentState = 0;       // 0=red, 1=yellow, 2=green, 3=yellow

void setup() {
  // Initialize 7-segment display pins
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); // Start with all segments OFF (Common Anode)
  }
  
  // Initialize traffic light pins
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  
  // Start with red light counting from 9
  setTrafficLight(0);
  displayNumber(9);
  Serial.println("Traffic Light Started - RED (9)");
}

void loop() {
  // Update display with current time
  displayNumber(currentTime);
  Serial.print("State: ");
  Serial.print(getStateName());
  Serial.print(" | Time: ");
  Serial.println(currentTime);
  
  delay(1000); // Wait 1 second
  currentTime--; // Decrement counter
  
  // Check if time for current countdown phase has elapsed
  if (currentTime < getMinTimeForState()) {
    changeState();
  }
}

void changeState() {
  // Move to next state
  currentState = (currentState + 1) % 4;
  
  switch(currentState) {
    case 0: // Red light (9-8-7-6-5-4)
      setTrafficLight(0);
      currentTime = 9; // Start from 9
      Serial.println("RED LIGHT - Counting 9 to 4");
      break;
      
    case 1: // First Yellow light (3-2-1)
      setTrafficLight(1);
      currentTime = 3; // Start from 3
      Serial.println("YELLOW LIGHT - Counting 3 to 1");
      break;
      
    case 2: // Green light (9-8-7-6-5-4)
      setTrafficLight(2);
      currentTime = 9; // Start from 9
      Serial.println("GREEN LIGHT - Counting 9 to 4");
      break;
      
    case 3: // Second Yellow light (3-2-1)
      setTrafficLight(1);
      currentTime = 3; // Start from 3
      Serial.println("YELLOW LIGHT - Counting 3 to 1");
      break;
  }
}

int getMinTimeForState() {
  switch(currentState) {
    case 0: // Red: stop at 4 (9→4 = 6 seconds)
    case 2: // Green: stop at 4 (9→4 = 6 seconds)
      return 4;
    case 1: // Yellow: stop at 1 (3→1 = 3 seconds)
    case 3: // Yellow: stop at 1 (3→1 = 3 seconds)
      return 1;
    default:
      return 1;
  }
}

String getStateName() {
  switch(currentState) {
    case 0: return "RED";
    case 1: return "YELLOW (after RED)";
    case 2: return "GREEN";
    case 3: return "YELLOW (after GREEN)";
    default: return "UNKNOWN";
  }
}

void setTrafficLight(int state) {
  // Turn all lights off first
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  
  // Turn on the appropriate light
  switch(state) {
    case 0: // Red
      digitalWrite(red, HIGH);
      break;
    case 1: // Yellow
      digitalWrite(yellow, HIGH);
      break;
    case 2: // Green
      digitalWrite(green, HIGH);
      break;
  }
}

void displayNumber(int number) {
  // COMMON ANODE patterns (inverted bits - 0=ON, 1=OFF)
  byte digitPatterns[10] = {
    B1111110, // 0 - segments: abcdef (inverted from B1111110)
    B0110000, // 1 - segments: bc     (inverted from B0110000)
    B1101101, // 2 - segments: abdeg  (inverted from B1101101)
    B1111001, // 3 - segments: abcdg  (inverted from B1111001)
    B0110011, // 4 - segments: bcfg   (inverted from B0110011)
    B1011011, // 5 - segments: acdfg  (inverted from B1011011)
    B1011111, // 6 - segments: acdefg (inverted from B1011111)
    B1110000, // 7 - segments: abc    (inverted from B1110000)
    B1111111, // 8 - segments: abcdefg (inverted from B1111111)
    B1111011  // 9 - segments: abcdfg (inverted from B1111011)
  };
  
  // Ensure number is within displayable range (0-9)
  if (number > 9) number = 9;
  if (number < 0) number = 0;
  
  byte pattern = digitPatterns[number];
  
  // Set each segment according to the pattern
  // For Common Anode: LOW turns segment ON, HIGH turns it OFF
  digitalWrite(a, pattern & B1000000 ? LOW : HIGH);
  digitalWrite(b, pattern & B0100000 ? LOW : HIGH);
  digitalWrite(c, pattern & B0010000 ? LOW : HIGH);
  digitalWrite(d, pattern & B0001000 ? LOW : HIGH);
  digitalWrite(e, pattern & B0000100 ? LOW : HIGH);
  digitalWrite(f, pattern & B0000010 ? LOW : HIGH);
  digitalWrite(g, pattern & B0000001 ? LOW : HIGH);
}

// Test function to verify display working
void testDisplay() {
  Serial.println("Testing Common Anode Display...");
  for (int i = 9; i >= 0; i--) {
    Serial.println(i);
    displayNumber(i);
    delay(1000);
  }
}