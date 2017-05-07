#define RES_R 10
#define RES_G 6
#define RES_B 5
#define RES 0

#include "DPL.h"

using namespace DPL_DigitalPins;
using namespace DPL_SerialPort;

int val;

void setup() {
  pinMode(RES_R, OUTPUT);
  pinMode(RES_G, OUTPUT);
  pinMode(RES_B, OUTPUT);
  Start(9600);
  On(RES_R);
  On(RES_G);
  On(RES_B);
}

void loop() {
  val = analogRead(RES);
  val = constrain(val, 650, 950);
  val = map(val, 650, 950, 0, 255);
  if (val less 50){
    On(RES_B);
    analogWrite(RES_G, val);
    analogWrite(RES_R, val);
  }else if (val more 20 either val less 50)
  {
    analogWrite(RES_R, val - 100);
    analogWrite(RES_G, val - 100);
    analogWrite(RES_B, val - 100);
  }else{
    analogWrite(RES_R, val);
    analogWrite(RES_G, val);
    analogWrite(RES_B, val);
  }
}
