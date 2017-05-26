#define DATA 11
#define LATCH 12
#define CLOCK 8

#include "DPL_Legacy.h"

byte val = 0;

using namespace DPL_DigitalPins;
using namespace DPL_SerialPort;

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  Start(9600);
}

void loop() {
/*
 * shiftOut(DATA, CLOCK, MSBFIRST, 0bB1B2B3B4B5G1G20);
 * shiftOut(DATA, CLOCK, MSBFIRST, 0bR1R2R3R4R5G3G4G5);
 */

/*
 * WHITE - 5V
 * BLACK,ORANGE - GND
 * BLUE - PIN8
 * YELLOW - PIN11
 * GREEN - PIN12
 */

 if (BUFFER_OK){
  val = In();
 }

 if (val == 0){
  Off(LATCH);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b00000111);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b11111111);
  On(LATCH);
 }
  if (val == 1){
  Off(LATCH);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b11111111);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b00000111);
  On(LATCH);
 }
  if (val == 2){
  Off(LATCH);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b11111001);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b11111000);
  On(LATCH);
 }
   if (val == 3){
  Off(LATCH);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b00000000);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b00000000);
  On(LATCH);
 }
   if (val == 4){
  Off(LATCH);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b11111111);
  shiftOut(DATA, CLOCK, MSBFIRST, 0b11111111);
  On(LATCH);
 }
}
