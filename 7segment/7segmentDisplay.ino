int a=2, b=3, c=4, d=5, e=6, f=7, g=8;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

// Function to display digits (Common Anode: LOW = ON)
void displayDigit(int num) {
  // digit patterns for 0–9
  // Order: a, b, c, d, e, f, g
  int digits[10][7] = {
    {LOW, LOW, LOW, LOW, LOW, LOW, HIGH},   // 0
    {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 1
    {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},  // 2
    {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW},  // 3
    {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW}, // 4
    {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW},  // 5
    {LOW, HIGH, LOW, LOW, LOW, LOW, LOW},   // 6
    {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH},// 7
    {LOW, LOW, LOW, LOW, LOW, LOW, LOW},    // 8
    {LOW, LOW, LOW, LOW, HIGH, LOW, LOW}    // 9
  };

  digitalWrite(a, digits[num][0]);
  digitalWrite(b, digits[num][1]);
  digitalWrite(c, digits[num][2]);
  digitalWrite(d, digits[num][3]);
  digitalWrite(e, digits[num][4]);
  digitalWrite(f, digits[num][5]);
  digitalWrite(g, digits[num][6]);
}

void loop() {
  for (int i=1; i<=9; i++) {
    displayDigit(i);
    delay(1000);  // 1 second delay like clock tick
  }
}
