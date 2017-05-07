#include "Arduino.h"
#include "DPL.h"

namespace DPL_PWM{
    int Get(int pinNum){
        return analogRead(pinNum);
    }
}

namespace DPL_RGB{
    RGB::RGB(int PIN_R, int PIN_G, int PIN_B){
        this->PIN_R = PIN_R;
        this->PIN_G = PIN_G;
        this->PIN_B = PIN_B;

        pinMode(this->PIN_R, OUTPUT);
        pinMode(this->PIN_G, OUTPUT);
        pinMode(this->PIN_B, OUTPUT);
    }

    void RGB::Set(byte R, byte G, byte B){
        this->R = R;
        this->G = G;
        this->B = B;

        analogWrite(PIN_R, this->R);
        analogWrite(PIN_G, this->G);
        analogWrite(PIN_B, this->B);
    }

    void Out(RGB LED){
        DPL_SerialPort::Out("R: " + S(LED.R) + " on Pin " + S(LED.PIN_R) + "   G: " + S(LED.G) + " on Pin " + S(LED.PIN_G) + "   B: " + S(LED.B) + " on Pin " + S(LED.PIN_B));
    }

    void Out(RGB LED, int mode){
        DPL_SerialPort::Out("R: " + S(LED.R) + " on Pin " + S(LED.PIN_R) + "   G: " + S(LED.G) + " on Pin " + S(LED.PIN_G) + "   B: " + S(LED.B) + " on Pin " + S(LED.PIN_B));
        if (mode == DPL_SerialPort::NEW_LINE)
            Serial.println("");
    }

    void Out(String NAME, RGB LED, int mode){
        DPL_SerialPort::Out(NAME + ": " + "R: " + S(LED.R) + " on Pin " + S(LED.PIN_R) + "   G: " + S(LED.G) + " on Pin " + S(LED.PIN_G) + "   B: " + S(LED.B) + " on Pin " + S(LED.PIN_B));
        if (mode == DPL_SerialPort::NEW_LINE)
            Serial.println("");
    }
}

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
