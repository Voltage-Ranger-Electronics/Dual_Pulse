// Dual Pulse Encoder Demo
// Author: Alexander Göbel
// For more information visit https://www.tindie.com/stores/alegro/ 
// For latest Software visit https://github.com/Voltage-Ranger-Electronics
// Created 10 Nov 2015
// For Arduino UNO w/ ATmega328
// Function     PIN
// V+          5V
// GND         GND
// S1          A2
// S2          A3

static int Enc1 = 2;
static int Enc2 = 3;

char input = 0;
char input_alt = 1;

int count = 0;

void setup() {
  // put your setup code here, to run once:
  // Serial Communication
  Serial.begin(9600);
  // Set Pullups
  pinMode(Enc1, INPUT_PULLUP);
  pinMode(Enc2, INPUT_PULLUP);
  // Interuppt to Pins
  attachInterrupt(digitalPinToInterrupt(Enc1), interuptEncode, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Enc2), interuptEncode, CHANGE);

  /* Function Declaration start*/
  signed char encode (char a, char b);
  /* Function Declaration end*/

  // Initialize encode
  encode (digitalRead(Enc1), digitalRead(Enc2));
}

void loop() {
  input = ((digitalRead(Enc1) + 1) * 10 + ((digitalRead(Enc2) + 1)));

  if (input != input_alt) {
    input_alt = input;
    Serial.print("Input: ");
    Serial.print(digitalRead(Enc1));
    Serial.print(digitalRead(Enc2));
    Serial.print("        Count: ");
    Serial.print(count);
    Serial.print("\n");
  }


}

void interuptEncode () {

  count += encode (digitalRead(Enc1), digitalRead(Enc2));

}

/* Function Implementation start*/
signed char encode (char x, char y) {
  // Initialize static variables ones with start value
  static char xAlt = 0;
  static char yAlt = 0;
  static char cR = 0;
  // Calculate what happend
  // Shift xAlt(high Byte) left and or with yAlt(low Byte)
  switch (xAlt << 1 | yAlt) {
    case 0:
      if ((x << 1 | y) == 2) {
        cR = 1;
      } else {
        cR = -1;
      }
      break;
    case 1:
      if ((x << 1 | y) == 0) {
        cR = 1;
      } else {
        cR = -1;
      }
      break;
    case 2:
      if ((x << 1 | y) == 3) {
        cR = 1;
      } else {
        cR = -1;
      }
      break;
    case 3:
      if ((x << 1 | y) == 1) {
        cR = 1;
      } else {
        cR = -1;
      }
      break;
    default:
      break;
  }
  // If no changes set cR to 0
  if (xAlt == x && yAlt == y) {
    cR = 0;
  }

  // Set old values again
  xAlt = x;
  yAlt = y;
  // Return what happend
  return cR;
}
/* Function Implementation end*/



