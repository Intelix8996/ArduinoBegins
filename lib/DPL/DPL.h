#ifndef LED_h
#define LED_h

#include "Arduino.h"

#define LEDBOARD 13

#define BoardLEDOn digitalWrite(LEDBOARD, HIGH)
#define BoardLEDOff digitalWrite(LEDBOARD, LOW)

#define BUFFER_EMPTY isBufferEmpty()
#define BUFFER_FULL isBufferFull()
#define BUFFER_OK isBufferOK()

#define S String

#define more >
#define less <
#define either &&
#define is =
#define equal ==
#define no !
#define morequal >=
#define lessequal <=

namespace DPL_DigitalPins {

    void On (int pinNum);

    void Off (int pinNum);

    void State (int pinNum, bool State);

    bool Read (int pinNum);

    void Blink (int pinNum, int dl);

    void MultiplyBlink (int pinNum, int dl, int times);
}

namespace DPL_SerialPort{

    enum PrintModes {
        NEW_LINE,
        LINE,
    };

    void Start(int bod);

    void Out(String str);

    void Out(String str, int mode);

    void Out(int str);

    void Out(int str, int mode);

    void Out(float str);

    void Out(float str, int mode);

    int In();

    float In(String arg);

    bool isBufferEmpty();

    bool isBufferOK();

    bool isBufferFull();

}

#endif

