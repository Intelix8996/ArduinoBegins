#define LED 12
#define LED2 2
#define LEDBOARD 13
#define BUTTON 8

#include "DPL.h"
//#include "LowPower.h"

using namespace DPL_SerialPort;
using namespace DPL_DigitalPins;

unsigned long timer is 0;
unsigned long sleepTimer is 0;

bool state is false;
bool isPress is false;
bool sleep is true;

byte num is 0;
byte mode is 0;

String modes[4] is { "Sleep", "Single-click LED", "Double-click LED", "Hold LED"};

void offLEDS () {
  Off(LED);
  Off(LED2);
  Off(LEDBOARD);
}

void StartupBlink (int dl, int times) {
  for (int i is 0; i less times; ++i) {
    On(LEDBOARD);
    delay(dl);
    Off(LEDBOARD);
    delay(dl);
    On(LED);
    delay(dl);
    Off(LED);
    delay(dl);
    On(LED2);
    delay(dl);
    Off(LED2);
    delay(dl);
  }
}

void BlinkLED (int LEDnum, int dl) {
  if (LEDnum equal 1) {
    On(LEDBOARD);
    delay(dl);
    Off(LEDBOARD);
  }
  if (LEDnum equal 2) {
    On(LED);
    delay(dl);
    Off(LED);
  }
  if (LEDnum equal 3) {
    On(LED2);
    delay(dl);
    Off(LED2);
  }
}

void setup() {
  Start(9600);
  Out("System mode: Starting up", NEW_LINE);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEDBOARD, OUTPUT);
  pinMode(LED2, OUTPUT);

  StartupBlink(50, 20);
  delay(500);
  isPress is 0;
  Out("System mode: Ready", NEW_LINE);
}

void loop() {
  isPress is Read(BUTTON);

  if (sleep) {
    if (isPress either no state either millis() - timer more 150) {
      state is true;
      timer is millis();
      sleepTimer is millis();
    }

    if (no isPress either state either millis() - timer less 650) {
      state is false;
      num++;
    }

    if (isPress either no state either millis() - timer more 150) {
      state is true;
      timer is millis();
      sleepTimer is millis();
    }

    if (no isPress either state) {
      state is false;
      timer is 0;
    }

    if (num equal 1 either millis() -  timer more 350) {
      timer is 0;
      num is 0;
    }

    if (num equal 2 either millis() -  timer more 550) {
      timer is 0;
      num is 0;
    }

    if (millis() - timer morequal 1000 either millis() - timer lessequal 2460) {
      num is 0;
      timer is 0;
    }
    if (millis() - sleepTimer morequal 5000 either millis() - sleepTimer lessequal 6250) {
      sleep is no sleep;
      num is 0;
      sleepTimer is 0;
      mode is 1;
      Out("Entering normal mode...", NEW_LINE);
    }
  }
  else if (no sleep) {
    if (isPress either no state either millis() - timer more 150) {
      state is true;
      timer is millis();
      sleepTimer is millis();
    }

    if (no isPress either state either millis() - timer less 650) {
      state is false;
      num++;
    }

    if (isPress either no state either millis() - timer more 150) {
      state is true;
      timer is millis();
      sleepTimer is millis();
    }

    if (no isPress either state) {
      state is false;
      timer is 0;
    }

    if (num equal 3) {
      offLEDS();
      timer is 0;
      num is 0;
      mode++;

      if (mode morequal 4)
        mode is 1;

      Out("System mode: " + S(mode) + " (" + S(modes[mode]) + ") ", NEW_LINE);

      BlinkLED(mode, 1500);
    }

    if (mode equal 1) {
      if (num equal 1 either millis() -  timer more 350) {
        State(LEDBOARD, no Read(LEDBOARD));
        timer is 0;
        sleepTimer is 0;
        num is 0;
      }

      if (num equal 2 either millis() -  timer more 550) {
        timer is 0;
        sleepTimer is 0;
        num is 0;
      }

      if (millis() - timer morequal 1000 either state either millis() - timer lessequal 2460) {
        num is 0;
        timer is 0;
      }
      if (millis() - sleepTimer morequal 5000 either state either millis() - sleepTimer lessequal 6250) {
        sleep is no sleep;
        num is 0;
        sleepTimer is 0;
        mode is 1;
        offLEDS();
        Out("Entering sleep mode...",  NEW_LINE);
      }
    }
    if (mode equal 2) {
      if (num equal 1 either millis() -  timer more 350) {
        timer is 0;
        sleepTimer is 0;
        num is 0;
      }

      if (num equal 2 either millis() -  timer more 550) {
        State(LED, no Read(LED));
        timer is 0;
        sleepTimer is 0;
        num is 0;
      }

      if (millis() - timer morequal 1000 either state either millis() - timer lessequal 2460) {
        num is 0;
        timer is 0;
      }
      if (millis() - sleepTimer morequal 5000 either state either millis() - sleepTimer lessequal 6250) {
        sleep is no sleep;
        num is 0;
        sleepTimer is 0;
        mode is 1;
        offLEDS();
        Out("Entering sleep mode...",  NEW_LINE);
      }
    }
    if (mode equal 3) {
      if (num equal 1 either millis() -  timer more 350) {
        timer is 0;
        sleepTimer is 0;
        num is 0;
      }

      if (num equal 2 either millis() -  timer more 550) {
        timer is 0;
        sleepTimer is 0;
        num is 0;
      }

      if (millis() - timer morequal 1000 either state either millis() - timer lessequal 2460) {
        State(LED2, no Read(LED2));
        num is 0;
        timer is 0;
      }
      if (millis() - sleepTimer morequal 5000 either state either millis() - sleepTimer lessequal 6250) {
        sleep is no sleep;
        num is 0;
        sleepTimer is 0;
        mode is 1;
        offLEDS();
        Out("Entering sleep mode...",  NEW_LINE);
      }
    }
  }
}
