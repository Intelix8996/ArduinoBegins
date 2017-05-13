#define RES_R 5
#define RES_G 6
#define RES_B 11
#define BUTTON 8

#include "DPL.h"

byte mode = 1;
bool state = 0;

byte Red = 0;
byte Green = 0;
byte Blue = 0;

unsigned long timer = 0;

using namespace DPL_PWM;
using namespace DPL_RGB;
using namespace DPL_SerialPort;
using namespace DPL_DigitalPins;

RGB LED(RES_R, RES_G, RES_B, NEGATIVE);

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  timer = millis();
  LED.Set(Red, Green, Blue);
  Start(9600);
}

void loop() {
  state = !Read(BUTTON);
  if (state either millis() - timer > 250) {
    ++mode;
    mode = ModeCrop(mode);
    timer = millis();
  }


  if (mode == 1) {
    Red = Get(0) / 4;
    LED.Set(Red, Green, Blue);
    Out("Changing: RED \t\t\t\t");
  }
  if (mode == 2) {
    Green = Get(0) / 4;
    LED.Set(Red, Green, Blue);
    Out("Changing: GREEN \t\t\t");
  }
  if (mode == 3) {
    Blue = Get(0) / 4;
    LED.Set(Red, Green, Blue);
    Out("Changing: BLUE \t\t\t\t");
  }

  Out("LED1", LED, NEW_LINE);
}

byte ModeCrop (byte mode) {
  if (mode > 3)
    mode = 1;

  return mode;
}


