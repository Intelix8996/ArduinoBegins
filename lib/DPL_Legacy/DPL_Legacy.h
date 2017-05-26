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

#define BLACK Color(0, 0, 0)
#define WHITE Color(255, 255, 255)
#define RED Color(255, 0, 0)
#define GREEN Color(0, 255, 0)
#define BLUE Color(0, 0, 255)

namespace DPL_PWM{
    #include "PWM.h"

    int Get(int pinNum);
}

namespace DPL_RGB{
    enum LED_Types{
        POSITIVE,
        NEGATIVE
    };

    struct Color{
    public:
        byte R = 0;
        byte G = 0;
        byte B = 0;

        Color (byte R, byte G, byte B);
    };


    class RGB{
    public:
        int PIN_R = 13;
        int PIN_G = 13;
        int PIN_B = 13;
        int TYPE = 0;

        Color color = Color(0, 0, 0);

        RGB(int PIN_R, int PIN_G, int PIN_B, int TYPE);

        void Set(byte R, byte G, byte B);

        void Set(Color cl);

        void Lerp(Color targetColor, int step);

        void Lerp(Color baseColor, Color targetColor, int step);
    };

    void Out(RGB LED_OBJ);

    void Out(RGB LED_OBJ, int mode);

    void Out(String NAME, RGB LED_OBJ, int mode);
}

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

    #include "comm_impl.h"

    void Start(int bod);

    bool isBufferEmpty();

    bool isBufferOK();

    bool isBufferFull();

}

#endif

