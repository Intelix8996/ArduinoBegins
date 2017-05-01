#define LED 12
#define LED2 2
#define LEDBOARD 13
#define BUTTON 8

#include "DPL.h"

using namespace DPL_SerialPort;
using namespace DPL_DigitalPins;

unsigned long timer = 0;
unsigned long sleepTimer = 0;

bool state = false;
bool isPress = false;
bool sleep = true;

int num = 0;
int mode = 0;

String modes[4] = { "Sleep", "Single-click LED", "Double-click LED", "Hold LED"};

void offLEDS () {
  Off(LED);
  Off(LED2);
  Off(LEDBOARD);
}

void StartupBlink (int dl, int times) {
  for (int i = 0; i < times; ++i) {
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
  if (LEDnum == 1) {
    On(LEDBOARD);
    delay(dl);
    Off(LEDBOARD);
  }
  if (LEDnum == 2) {
    On(LED);
    delay(dl);
    Off(LED);
  }
  if (LEDnum == 3) {
    On(LED2);
    delay(dl);
    Off(LED2);
  }
}

void setup() {
  Start(9600);
  PrlnStr("System mode: Starting up");

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEDBOARD, OUTPUT);
  pinMode(LED2, OUTPUT);

  StartupBlink(50, 20);
  delay(500);
  isPress = 0;
  PrlnStr("System mode: Ready");
}

void loop() {
  isPress = Read(BUTTON);

  if (sleep) {
    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state && millis() - timer < 650) {
      state = false;
      num++;
    }

    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state) {
      state = false;
      timer = 0;
    }

    if (num == 1 && millis() -  timer > 350) {
      timer = 0;
      num = 0;
    }

    if (num == 2 && millis() -  timer > 550) {
      timer = 0;
      num = 0;
    }

    if (millis() - timer >= 1000 && millis() - timer <= 2460) {
      num = 0;
      timer = 0;
    }
    if (millis() - sleepTimer >= 5000 && millis() - sleepTimer <= 6250) {
      sleep = !sleep;
      num = 0;
      sleepTimer = 0;
      mode = 1;
      PrlnStr("Entering normal mode...");
    }
  }
  else if (!sleep) {
    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state && millis() - timer < 650) {
      state = false;
      num++;
    }

    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state) {
      state = false;
      timer = 0;
    }

    if (num == 3) {
      offLEDS();
      timer = 0;
      num = 0;
      mode++;

      if (mode >= 4)
        mode = 1;

      PrStr("System mode: ");
      PrNum(mode);
      PrStr(" (");
      PrStr(modes[mode]);
      PrlnStr(") ");

      BlinkLED(mode, 1500);
    }

    if (mode == 1) {
      if (num == 1 && millis() -  timer > 350) {
        State(LEDBOARD, !Read(LEDBOARD));
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (num == 2 && millis() -  timer > 550) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (millis() - timer >= 1000 && state && millis() - timer <= 2460) {
        num = 0;
        timer = 0;
      }
      if (millis() - sleepTimer >= 5000 && state && millis() - sleepTimer <= 6250) {
        sleep = !sleep;
        num = 0;
        sleepTimer = 0;
        mode = 1;
        offLEDS();
        PrlnStr("Entering sleep mode...");
      }
    }
    if (mode == 2) {
      if (num == 1 && millis() -  timer > 350) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (num == 2 && millis() -  timer > 550) {
        State(LED, !Read(LED));
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (millis() - timer >= 1000 && state && millis() - timer <= 2460) {
        num = 0;
        timer = 0;
      }
      if (millis() - sleepTimer >= 5000 && state && millis() - sleepTimer <= 6250) {
        sleep = !sleep;
        num = 0;
        sleepTimer = 0;
        mode = 1;
        offLEDS();
        PrlnStr("Entering sleep mode...");
      }
    }
    if (mode == 3) {
      if (num == 1 && millis() -  timer > 350) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (num == 2 && millis() -  timer > 550) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (millis() - timer >= 1000 && state && millis() - timer <= 2460) {
        State(LED2, !Read(LED2));
        num = 0;
        timer = 0;
      }
      if (millis() - sleepTimer >= 5000 && state && millis() - sleepTimer <= 6250) {
        sleep = !sleep;
        num = 0;
        sleepTimer = 0;
        mode = 1;
        offLEDS();
        PrlnStr("Entering sleep mode...");
      }
    }
  }
}
