#include "Arduino.h"
#include "DPL.h"

namespace DPL_RGB{

    Color::Color (byte R, byte G, byte B){
        this->R = R;
        this->G = G;
        this->B = B;
    }

    RGB::RGB(int PIN_R, int PIN_G, int PIN_B, int TYPE){
        this->PIN_R = PIN_R;
        this->PIN_G = PIN_G;
        this->PIN_B = PIN_B;
        this->TYPE = TYPE;

        pinMode(this->PIN_R, OUTPUT);
        pinMode(this->PIN_G, OUTPUT);
        pinMode(this->PIN_B, OUTPUT);
    }

    void RGB::RGB_IO_SETCOLOR(byte R, byte G, byte B){
        color.R = R;
        color.G = G;
        color.B = B;

        if (TYPE == POSITIVE){
            analogWrite(PIN_R, color.R);
            analogWrite(PIN_G, color.G);
            analogWrite(PIN_B, color.B);
        }
        if (TYPE == NEGATIVE){
            analogWrite(PIN_R, 255-color.R);
            analogWrite(PIN_G, 255-color.G);
            analogWrite(PIN_B, 255-color.B);
        }
    }

    void RGB::RGB_IO_SETCOLOR(Color cl){
        this->color.R = cl.R;
        this->color.G = cl.G;
        this->color.B = cl.B;

        if (TYPE == POSITIVE){
            analogWrite(PIN_R, color.R);
            analogWrite(PIN_G, color.G);
            analogWrite(PIN_B, color.B);
        }
        if (TYPE == NEGATIVE){
            analogWrite(PIN_R, 255-color.R);
            analogWrite(PIN_G, 255-color.G);
            analogWrite(PIN_B, 255-color.B);
        }
    }

    void RGB::RGB_IO_MACRO_LERPCOLOR(Color targetColor, int step){
        while (true){
            if (color.R < targetColor.R && color.R + step <= 255)
                color.R += step;
            if (color.R > targetColor.R && color.R - step >= 0)
                color.R -= step;
            if (color.G < targetColor.G && color.G + step <= 255)
                color.G += step;
            if (color.G > targetColor.G && color.G - step >= 0)
                color.G -= step;
            if (color.B < targetColor.B && color.B + step <= 255)
                color.B += step;
            if (color.B > targetColor.B && color.B - step >= 0)
                color.B -= step;

            if (color.R <= targetColor.R+step && color.R >= targetColor.R-step && color.G <= targetColor.G+step && color.G >= targetColor.G-step && color.B <= targetColor.B+step && color.B >= targetColor.B-step)
                break;

            Set(color);
            delay(1);
        }
    }

    void RGB::RGB_IO_MACRO_LERPCOLOR(Color baseColor, Color targetColor, int step){
        color = baseColor;

        while (true){
            if (color.R < targetColor.R && color.R + step <= 255)
                color.R += step;
            if (color.R > targetColor.R && color.R - step >= 0)
                color.R -= step;
            if (color.G < targetColor.G && color.G + step <= 255)
                color.G += step;
            if (color.G > targetColor.G && color.G - step >= 0)
                color.G -= step;
            if (color.B < targetColor.B && color.B + step <= 255)
                color.B += step;
            if (color.B > targetColor.B && color.B - step >= 0)
                color.B -= step;

            if (color.R <= targetColor.R+step && color.R >= targetColor.R-step && color.G <= targetColor.G+step && color.G >= targetColor.G-step && color.B <= targetColor.B+step && color.B >= targetColor.B-step)
                break;

            Set(color);
            delay(1);
        }
    }
}

namespace DPL_Pins {
    Pin::Pin(byte pinNumber, int mode){
        this->pinNumber = pinNumber;
        pinMode(this->pinNumber, mode);
    }

    void Pin::DIGITAL_IO_SETLOGICLEVEL_HIGH (){
        digitalWrite(pinNumber, HIGH);
    }

    void Pin::DIGITAL_IO_SETLOGICLEVEL_LOW (){
        digitalWrite(pinNumber, LOW);
    }

    void Pin::DIGITAL_IO_SETLOGICLEVEL_CUSTOMSTATE(bool State){
        digitalWrite(pinNumber, State);
    }

    bool Pin::DIGITAL_IO_READLOGICLEVEL (){
        return digitalRead(pinNumber);
    }

    void Pin::DIGITAL_IO_MACRO_BLINK (int dl) {
        On();
        delay(dl);
        Off();
    }

    void Pin::DIGITAL_IO_MACRO_BLINK_MULTIPLY (int dl, int times) {
      for (int i = 0; i < times; ++i) {
        On();
        delay(dl);
        Off();
        delay(dl);
      }
    }

    int Pin::ANALOG_IO_READPWMSIGNAL(){
        return analogRead(pinNumber);
    }
}

namespace DPL_SerialPort{
    SerialPort::SerialPort(int bod){
        this->bod = bod;
        Serial.begin(this->bod);
    }

    void SerialPort::SERIAL_IO_SERIALCONNECTION_BEGIN(){
        Serial.begin(bod);
    }

    int SerialPort::SERIAL_IO_READNUMBER (){
        return Serial.parseInt();
    }

    float SerialPort::SERIAL_IO_READNUMBER (String arg){
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
