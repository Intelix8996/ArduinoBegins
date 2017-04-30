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
    void PrNum(int i){
        Serial.print(i);
    }
    void PrStr(char str[]){
        Serial.print(str);
    }
    void PrlnNum(int i){
        Serial.println(i);
    }
    void PrlnStr(String str){
        Serial.println(str);
    }
    int ReadInt(){
        return Serial.parseInt();
    }
    float ReadFloat(){
        return Serial.parseFloat();
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
