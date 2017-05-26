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
}

namespace DPL_Pins {
    class Pin {
    public:
        byte pinNumber = 0;

        Pin(byte pinNumber, int mode);

        void On ();

        void Off ();

        void State (bool State);

        bool Read ();

        void Blink (int dl);

        void MultiplyBlink (int dl, int times);

        #include "PWM.h"

        int Get();
    };
}

namespace DPL_SerialPort{

    enum PrintModes {
        NEW_LINE,
        LINE,
    };

    class SerialPort{
    public:
        int bod = 9600;

        SerialPort(int bod);

        #include "comm_impl.h"

        void Start();
    };

    bool isBufferEmpty();

    bool isBufferOK();

    bool isBufferFull();

}

#endif

