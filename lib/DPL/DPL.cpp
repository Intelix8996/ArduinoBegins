#include "Arduino.h"
#include "DPL.h"

namespace DPL_PWM{
    int Get(int pinNum){
        return analogRead(pinNum);
    }
}

namespace DPL_RGB{

    Color::Color (byte R, byte G, byte B){
        this->R = R;
        this->G = G;
        this->B = B;
    }

    RGB::RGB(int PIN_R, int PIN_G, int PIN_B){
        this->PIN_R = PIN_R;
        this->PIN_G = PIN_G;
        this->PIN_B = PIN_B;

        pinMode(this->PIN_R, OUTPUT);
        pinMode(this->PIN_G, OUTPUT);
        pinMode(this->PIN_B, OUTPUT);
    }

    void RGB::Set(byte R, byte G, byte B){
        this->color.R = R;
        this->color.G = G;
        this->color.B = B;

        analogWrite(PIN_R, this->color.R);
        analogWrite(PIN_G, this->color.G);
        analogWrite(PIN_B, this->color.B);
    }

    void RGB::Set(Color cl){
        this->color.R = cl.R;
        this->color.G = cl.G;
        this->color.B = cl.B;

        analogWrite(PIN_R, this->color.R);
        analogWrite(PIN_G, this->color.G);
        analogWrite(PIN_B, this->color.B);
    }

    void RGB::Lerp(Color targetColor, int step){
        byte maxTargetNum = 0;
        byte minTargetNum = 0;
        byte minBaseNum = 0;

        if (targetColor.R > targetColor.G && targetColor.R > targetColor.B)
            maxTargetNum = targetColor.R;
        if (targetColor.G > targetColor.R && targetColor.G > targetColor.B)
            maxTargetNum = targetColor.G;
        if (targetColor.B > targetColor.G && targetColor.B > targetColor.R)
            maxTargetNum = targetColor.B;

        if (targetColor.R < targetColor.G && targetColor.R < targetColor.B)
            minTargetNum = targetColor.R;
        if (targetColor.G < targetColor.R && targetColor.G < targetColor.B)
            minTargetNum = targetColor.G;
        if (targetColor.B < targetColor.G && targetColor.B < targetColor.R)
            minTargetNum = targetColor.B;

        if(color.R < color.G && color.R < color.B)
            minBaseNum = color.R;
        if(color.G < color.R && color.G < color.B)
            minBaseNum = color.G;
        if(color.B < color.G && color.B < color.R)
            minBaseNum = color.B;

        if (minBaseNum < maxTargetNum){
            for (int i = 0; i < maxTargetNum; i += step){
                if (color.R < targetColor.R)
                    color.R += step;
                if (color.G < targetColor.G)
                    color.G += step;
                if (color.B < targetColor.B)
                    color.B += step;

                Set(color);
                DPL_SerialPort::Out(S(color.R) + " " + S(color.G) + " " + S(color.B), 0);
                delay(1);
            }
        }
        else
        {
            for (int i = 255; i > minTargetNum; i -= step){
                if (color.R > targetColor.R)
                    color.R -= step;
                if (color.G > targetColor.G)
                    color.G -= step;
                if (color.B > targetColor.B)
                    color.B -= step;

                Set(color);
                DPL_SerialPort::Out(S(color.R) + " " + S(color.G) + " " + S(color.B), 0);
                delay(1);
            }
        }
    }

    void RGB::Lerp(Color baseColor, Color targetColor, int step){
        color = baseColor;

        byte maxTargetNum = 0;
        byte minTargetNum = 0;
        byte minBaseNum = 0;

        if (targetColor.R >= targetColor.G && targetColor.R >= targetColor.B)
            maxTargetNum = targetColor.R;
        if (targetColor.G >= targetColor.R && targetColor.G >= targetColor.B)
            maxTargetNum = targetColor.G;
        if (targetColor.B >= targetColor.G && targetColor.B >= targetColor.R)
            maxTargetNum = targetColor.B;

        if (targetColor.R <= targetColor.G && targetColor.R <= targetColor.B)
            minTargetNum = targetColor.R;
        if (targetColor.G <= targetColor.R && targetColor.G <= targetColor.B)
            minTargetNum = targetColor.G;
        if (targetColor.B <= targetColor.G && targetColor.B <= targetColor.R)
            minTargetNum = targetColor.B;

        if(color.R <= color.G && color.R <= color.B)
            minBaseNum = color.R;
        if(color.G <= color.R && color.G <= color.B)
            minBaseNum = color.G;
        if(color.B <= color.G && color.B <= color.R)
            minBaseNum = color.B;

        if (minBaseNum < maxTargetNum){
            for (int i = 0; i < maxTargetNum; i += step){
                if (color.R < targetColor.R)
                    color.R += step;
                if (color.G < targetColor.G)
                    color.G += step;
                if (color.B < targetColor.B)
                    color.B += step;

                Set(color);
                delay(1);
            }
        }
        else
        {
            for (int i = 255; i > minTargetNum; i -= step){
                if (color.R > targetColor.R)
                    color.R -= step;
                if (color.G > targetColor.G)
                    color.G -= step;
                if (color.B > targetColor.B)
                    color.B -= step;

                Set(color);
                delay(1);
            }
        }
    }

    void Out(RGB LED){
        DPL_SerialPort::Out("R: " + S(LED.color.R) + " on Pin " + S(LED.PIN_R) + "   G: " + S(LED.color.G) + " on Pin " + S(LED.PIN_G) + "   B: " + S(LED.color.B) + " on Pin " + S(LED.PIN_B));
    }

    void Out(RGB LED, int mode){
        DPL_SerialPort::Out("R: " + S(LED.color.R) + " on Pin " + S(LED.PIN_R) + "   G: " + S(LED.color.G) + " on Pin " + S(LED.PIN_G) + "   B: " + S(LED.color.B) + " on Pin " + S(LED.PIN_B));
        if (mode == DPL_SerialPort::NEW_LINE)
            Serial.println("");
    }

    void Out(String NAME, RGB LED, int mode){
        DPL_SerialPort::Out(NAME + ": " + "R: " + S(LED.color.R) + " on Pin " + S(LED.PIN_R) + "   G: " + S(LED.color.G) + " on Pin " + S(LED.PIN_G) + "   B: " + S(LED.color.B) + " on Pin " + S(LED.PIN_B));
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
