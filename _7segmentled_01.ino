/* _7segmentled_01
   1.0: Driving the right digit of a 2-digit 7-segment led common anode display.
   1.1: Now going to try shutting off the display once in a while with an NPN transistor.
   1.2: Now trying to have one digit displaying while the other isn't.  Added another xistor.
   1.3: Now that I have the right segments in series between left-digit and right-digit,
        I want to switch between digits enabled and digits displayed fast enough to give the 
        illusion that both digits are always on.
*/

byte seven_seg_digits[10][7] = {
  {0,0,0,0,0,0,1}, // = 0
  {1,0,0,1,1,1,1}, // = 1
  {0,0,1,0,0,1,0}, // = 2
  {0,0,0,0,1,1,0}, // = 3
  {1,0,0,1,1,0,0}, // = 4
  {0,1,0,0,1,0,0}, // = 5
  {0,1,0,0,0,0,0}, // = 6
  {0,0,0,1,1,1,1}, // = 7
  {0,0,0,0,0,0,0}, // = 8
  {0,0,0,1,1,0,0} // = 9
};

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);  // right digit transistor control
  pinMode(10, OUTPUT); // left digit transistor control
  digitalWrite(9, HIGH); // i want rd high right away
  digitalWrite(10, LOW); // i want ld low right away
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void render2Digits(byte inputNumber) {
  // keeps the number between 0 inclusive and 99 inclusive.
  if (inputNumber > 99) {
    inputNumber = 99;
  } else if (inputNumber < 0) {
    inputNumber = 0;
  }
  int quotient10 = inputNumber / 10;
  int remainder10 = inputNumber % 10;
  for (byte intervals = 3; intervals > 0; --intervals) {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH); 
    sevenSegWrite((byte) quotient10);
    delay(166); // 1/6th of a second
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW); 
    sevenSegWrite((byte) remainder10);
    delay(166); // 1/6th of a second
  }

void loop() {
  for (byte count = 99; count > 0; --count) {
    render2Digits(count);
  }
  delay(3000);
}
