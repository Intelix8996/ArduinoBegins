#define RES 0
#define LED 11
#define LED2 6

#include "DPL.h"

using namespace DPL_SerialPort;
using namespace DPL_DigitalPins;

int val = 0;

void setup() {
  pinMode(RES, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  FirstLEDBundle();
  SecondLEDBundle();
}

void FirstLEDBundle (){
  val = analogRead(RES);
  val = constrain(val, 650, 950);
  val = map(val, 650, 950, 0, 255);
  analogWrite(LED, val);
}

void SecondLEDBundle (){
  val = analogRead(RES);
  val = constrain(val, 650, 950);
  val = map(val, 650, 950, 0, 255);
  val = 255 - val;
  analogWrite(LED2, val);
}

