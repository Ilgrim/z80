// govern a Z80 from an Arduino

// the z80 code is stored in an array
// the file will be generated by assemble.py
// an example is part of the repo
#include "z80_code.h"

int spd = 0; //clock speed in ms delays

void reset() {
  // reset z80 (four cycles);
  // set reset to low
  PORTC = PORTC & B11110111;
  // change clock 10 times (equals 5 cycles)
  for (int i=0; i<10; i++) {
    PORTC = PORTC ^ B00100000;
  }
  // set reset to high
  PORTC = PORTC | B00001000;
}

void setup() {
  // use D port as Data bus
  // output only simulating ROM
  // however set inactive/INPUT For now
  DDRD = B00000000;
  // use B port as Address bus
  // which has six lines available
  // 64 byte address space
  DDRB = B00000000;
  // use C port as Control bus
  // 2 mreq <- in
  // 3 reset -> out
  // 4 read <- in
  // 5 clock -> out
  DDRC = B00101000;
  // call reset
  reset();
}

void loop() {
  PORTC = PORTC | B00100000;
  // clock high phase, a good space for debugging
  PORTC = PORTC ^ B00100000;
  if (!(PINC & B00010100)) {
    // set Port D as output 
    DDRD = B11111111;
    // fetch code
    PORTD = code[PINB];
  }
  else {
    // set PORT D to input state in order not to 
    // interfere with other data bus operations
    DDRD = B00000000;
  }
}
