#include "Arduino.h"
#include "DPL.h"

namespace DPL_DigitalPins {
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
}

namespace DPL_SerialPort{

    void Start(int bod){
        Serial.begin(bod);
    }

    int In (){
        return Serial.parseInt();
    }

    float In (String arg){
        if (arg == "-f")
            return Serial.parseFloat();
        if (arg == "-d")
            return Serial.parseFloat();
        else
            return Serial.parseInt();
    }

    bool isBufferEmpty(){
        if (Serial.available() == 0)
            return true;
        else
            return false;
    }

    bool isBufferOK(){
        if (Serial.available() > 0 && Serial.available() < 64)
            return true;
        else
            return false;
    }

    bool isBufferFull(){
        if (Serial.available() == 64)
            return true;
        else
            return false;
    }
}
