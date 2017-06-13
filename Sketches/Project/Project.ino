#include <LiquidCrystal_I2C.h>

#include "DPL.h"

#define LBLUE Color(0, 255, 255)
#define PURPLE Color(255, 0, 255)
#define YELLOW Color(255, 255, 0)

using namespace DPL_Pins;
using namespace DPL_SerialPort;
using namespace DPL_RGB;

bool isSet[4] = {false, false, false, false};

const byte LEDAmount = 4;

LiquidCrystal_I2C LCD(0x27, 16, 2);

Pin enc_A(11, INPUT);
Pin enc_B(12, INPUT);
Pin Button(8, INPUT_PULLUP);

RGB LED1(2, 3, 4, NEGATIVE);
RGB LED2(5, 6, 7, NEGATIVE);
RGB LED3(9, 10, A1, NEGATIVE);
RGB LED4(A0, A2, A3, NEGATIVE);

RGB LEDS[LEDAmount] = {LED1, LED2, LED3, LED4};

Color UNLOCKCOLORS[4] = {BLACK, BLACK, BLACK, BLACK};

int Count = 0;

unsigned long timer  = 0;

SerialPort SC(9600);

bool enc_A_prev = false;

enum Modes {
  LOCKED,
  UNLOCKED,
};

void setup() {
  SC.Start();
  timer = millis();
  LEDS[0].Set(0, 0, 0);
  LEDS[1].Set(0, 0, 0);
  LEDS[2].Set(0, 0, 0);
  LEDS[3].Set(0, 0, 0);
  LCDInit();
}

void loop() {
  EncHandler();
  Loop(Count);
}

void Loop (int val) {
  bool BUTTON = !Button.Read();

  if (millis() - timer >= 500) {
    for (int i = 0; i < LEDAmount; ++i) {
      int Buff = random(1, 7);

      switch (Buff) {
        case 1: LEDS[i].Set(WHITE); break;
        case 2: LEDS[i].Set(RED); break;
        case 3: LEDS[i].Set(GREEN); break;
        case 4: LEDS[i].Set(BLUE); break;
        case 5: LEDS[i].Set(YELLOW); break;
        case 6: LEDS[i].Set(LBLUE); break;
        default: LEDS[i].Set(PURPLE); break;
      }
    }
    timer = millis();
  }
  if (BUTTON) {
    if (!isSet[Count - 1]){
      UNLOCKCOLORS[Count - 1] = LEDS[Count - 1].color;
      LCD.setCursor(Count * 3, 1);
      LCD.print("|");
      isSet[Count - 1] = true;
    }
    for (int i = 0; i < 4; ++i){
      SC.Out(S(UNLOCKCOLORS[i].R) + " " + S(UNLOCKCOLORS[i].G) + " " + S(UNLOCKCOLORS[i].B) +"\t\t" , LINE);
      }
      SC.Out(" ", NEW_LINE);
      delay(200);
  }

  if (isSet[0] && isSet[1] && isSet[2] && isSet[3])
    Lock();
}

void EncHandler () {
  bool A = enc_A.Read();
  bool B = enc_B.Read();

  if (!A && enc_A_prev) {
    if (B)
      --Count;
    else
      ++Count;

    Count = constrain(Count, 1, 4);
  }

  enc_A_prev = A;
  SetBlink(Count);
}

void LCDInit() {
  LCD.begin();
  LCD.print("   1  2  3  4");
  LCD.setCursor(0, 1);
  LCD.print("   `  `  `  `");
}

void SetBlink(byte val) {
  if (val > 0) {
    LCD.setCursor(val * 3, 0);
    LCD.blink();
  } else {
    LCD.noBlink();
  }
}

void Lock(){
  for (int i = 0; i < 4; ++i){
    isSet[i] = true;
  }
  LCD.setCursor(0,0);
  LCD.print("  Pass is set  ");
  LCD.setCursor(0,1);
  LCD.print("                ");
}

void Unlock(){
  for (int i = 0; i < 4; ++i){
    isSet[i] = false;
  }
}

