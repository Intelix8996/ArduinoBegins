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

#define Set RGB_IO_SETCOLOR
#define Lerp RGB_IO_MACRO_LERPCOLOR

#define On DIGITAL_IO_SETLOGICLEVEL_HIGH
#define Off DIGITAL_IO_SETLOGICLEVEL_LOW
#define setState DIGITAL_IO_SETLOGICLEVEL_CUSTOMSTATE
#define readState DIGITAL_IO_READLOGICLEVEL
#define Blink DIGITAL_IO_MACRO_BLINK
#define MultiplyBlink DIGITAL_IO_MACRO_BLINK_MULTIPLY
#define setPWM ANALOG_IO_SETPWMSIGNAL
#define readPWM ANALOG_IO_READPWMSIGNAL

#define Start SERIAL_IO_SERIALCONNECTION_BEGIN
#define Init SERIAL_IO_SERIALCONNECTION_BEGIN
#define Send SERIAL_IO_SENDDATA
#define Receive SERIAL_IO_READNUMBER

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
        //Set
        void RGB_IO_SETCOLOR(byte R, byte G, byte B);
        //Set
        void RGB_IO_SETCOLOR(Color cl);
        //Lerp
        void RGB_IO_MACRO_LERPCOLOR(Color targetColor, int step);
        //Lerp
        void RGB_IO_MACRO_LERPCOLOR(Color baseColor, Color targetColor, int step);
    };
}

namespace DPL_Pins {
    class Pin {
    public:
        byte pinNumber = 0;

        Pin(byte pinNumber, int mode);

        //On
        void DIGITAL_IO_SETLOGICLEVEL_HIGH ();
        //Off
        void DIGITAL_IO_SETLOGICLEVEL_LOW ();
        //SetState
        void DIGITAL_IO_SETLOGICLEVEL_CUSTOMSTATE (bool State);
        //Read
        bool DIGITAL_IO_READLOGICLEVEL ();
        //Blink
        void DIGITAL_IO_MACRO_BLINK (int dl);
        //MultiplyBlink
        void DIGITAL_IO_MACRO_BLINK_MULTIPLY (int dl, int times);
        //Set
        #include "PWM.h"
        //Get
        int ANALOG_IO_READPWMSIGNAL();
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
        //In and Out
        #include "comm_impl.h"
        //Start
        void SERIAL_IO_SERIALCONNECTION_BEGIN ();
    };

    bool isBufferEmpty();

    bool isBufferOK();

    bool isBufferFull();

}

#endif

