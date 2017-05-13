#define RES_R 5
#define RES_G 6
#define RES_B 11

#include "DPL.h"

using namespace DPL_PWM;
using namespace DPL_RGB;
using namespace DPL_SerialPort;

RGB LED(5, 6, 11, NEGATIVE);

void setup() {
  Start(9600);
  Out("Ready: ", NEW_LINE);
  LED.Set(0,0,0);
}

void loop() {
  LED.Set(Color(Get(2)/4, Get(1)/4, Get(0)/4));
  Out("LED1", LED, NEW_LINE);
}
