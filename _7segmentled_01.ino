/* _7segmentled_01
   1.0: Driving the right digit of a 2-digit 7-segment led common anode display.
   1.1: Now going to try shutting off the display once in a while with an NPN transistor.
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
  pinMode(9, OUTPUT); // transistor control
  digitalWrite(9, HIGH); // i want it high right away
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  for (byte count = 10; count > 0; --count) {
    delay(1000);
    // i wonder if i'll see odd numbers or even numbers because of this trick?
    if (count % 2 == 0) {
      digitalWrite(9, LOW);
    } else {
      digitalWrite(9, HIGH);
    }
    sevenSegWrite(count - 1);
  }
  delay(3000);
}
