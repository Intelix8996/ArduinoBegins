#include "Arduino.h"
#include "LED.h"

void On (int pinNum){
    digitalWrite(pinNum, HIGH);
}

void Off (int pinNum){
    digitalWrite(pinNum, LOW);
}
