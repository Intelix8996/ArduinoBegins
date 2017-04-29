#include "Arduino.h"
#include "DPL.h"

void On (int pinNum){
    digitalWrite(pinNum, HIGH);
}

void Off (int pinNum){
    digitalWrite(pinNum, LOW);
}

void State(int pinNum, bool State){
    digitalWrite(pinNum, State);
}

bool Read (int pinNum){
    return digitalRead(pinNum);
}

void Blink (int pinNum, int dl) {
    On(pinNum);
    delay(dl);
    Off(pinNum);
}

void MultiplyBlink (int pinNum, int dl, int times) {
  for (int i = 0; i < times; ++i) {
    On(pinNum);
    delay(dl);
    Off(pinNum);
    delay(dl);
  }
}
