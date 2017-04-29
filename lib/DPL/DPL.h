#ifndef LED_h
#define LED_h

#include "Arduino.h"

#define LEDBOARD 13

#define BoardLEDOn digitalWrite(LEDBOARD, HIGH)
#define BoardLEDOff digitalWrite(LEDBOARD, LOW)

void On (int pinNum);

void Off (int pinNum);

void State (int pinNum, bool State);

bool Read (int pinNum);

void Blink (int pinNum, int dl);

void MultiplyBlink (int pinNum, int dl, int times);

#endif

