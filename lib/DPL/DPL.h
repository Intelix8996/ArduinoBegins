#ifndef LED_h
#define LED_h

#include "Arduino.h"

#define LEDBOARD 13

#define BoardLEDOn digitalWrite(LEDBOARD, HIGH)
#define BoardLEDOff digitalWrite(LEDBOARD, LOW)

#define BUFFER_EMPTY isBufferEmpty()
#define BUFFER_FULL isBufferFull()
#define BUFFER_OK isBufferOK()

namespace DPL_DigitalPins {

    void On (int pinNum);

    void Off (int pinNum);

    void State (int pinNum, bool State);

    bool Read (int pinNum);

    void Blink (int pinNum, int dl);

    void MultiplyBlink (int pinNum, int dl, int times);
}

namespace DPL_SerialPort{

    void Start(int bod);

    void PrNum(int i);

    void PrStr(String str);

    void PrlnNum(int i);

    void PrlnStr(String str);

    int ReadInt();

    float ReadFloat();

    bool isBufferEmpty();

    bool isBufferOK();

    bool isBufferFull();

}

#endif

