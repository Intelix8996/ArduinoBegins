#include <LiquidCrystal_I2C.h>

#include "DPL.h"

#define LBLUE Color(0, 255, 255)
#define PURPLE Color(255, 0, 255)
#define YELLOW Color(255, 255, 0)

using namespace DPL_Pins;
using namespace DPL_SerialPort;
using namespace DPL_RGB;

bool isSet[4] = {false, false, false, false};

bool isLocked = false;

const byte LEDAmount = 4;

float DELAY = 1000;
bool isDELAYSet = false;

LiquidCrystal_I2C LCD(0x27, 16, 2);

Pin enc_A(11, INPUT);
Pin enc_B(12, INPUT);
Pin Button(8, INPUT_PULLUP);

Pin LockPin(1, OUTPUT);

RGB LED1(2, 3, 4, NEGATIVE);
RGB LED2(5, 6, 7, NEGATIVE);
RGB LED3(9, 10, A1, NEGATIVE);
RGB LED4(A0, A2, A3, NEGATIVE);

RGB LEDS[LEDAmount] = {LED1, LED2, LED3, LED4};

Color UNLOCKCOLORS[4] = {BLACK, BLACK, BLACK, BLACK};

Color ENTEREDCOLORS[4] = {BLACK, BLACK, BLACK, BLACK};

int Count = 0;

unsigned long timer  = 0;

SerialPort SC(9600);

bool enc_A_prev = false;
int delay_prev = 0;

enum Modes {
  LOCKED,
  UNLOCKED,
};

void setup() {
  timer = millis();
  LEDS[0].Set(0, 0, 0);
  LEDS[1].Set(0, 0, 0);
  LEDS[2].Set(0, 0, 0);
  LEDS[3].Set(0, 0, 0);
  LCDInit();

  LCD.setCursor(0,0);
  LCD.print("   Enter delay  ");
  LCD.setCursor(0,1);
  LCD.print("                ");
  PreSetup();
}

void loop() {
  if (!isDELAYSet)
    PreSetup ();
  else{  
    EncHandler();
    if (!isLocked)
      Loop(Count);
    if (isLocked)
      LockedLoop(Count); 
  }
}

void PreSetup (){
  bool A = enc_A.Read();
  bool B = enc_B.Read();

  if (!A && enc_A_prev && millis() - timer >= 25) {
    if (B){
      if (DELAY <= 3000)
        DELAY -= 10;
      else if (DELAY > 3000 && DELAY <= 15000)
        DELAY -= 100;
      else if (DELAY > 15000)
        DELAY -= 1000;
    }
    else{
      if (DELAY <= 3000)
        DELAY += 10;
      else if (DELAY > 3000 && DELAY <= 15000)
        DELAY += 100;
      else if (DELAY > 15000)
        DELAY += 1000;
    }
    timer = millis();

    DELAY = constrain(DELAY, 0, 100000);
  }

  enc_A_prev = A;

  if (delay_prev != DELAY){
    LCD.setCursor(0,1);
    LCD.print("      ");
    LCD.setCursor(6,1);
    LCD.print(DELAY/1000);
    LCD.print("sec   ");
  }

  if (!Button.Read()){
    isDELAYSet = true;
    LCDInit();
  }

  delay_prev = DELAY;
}

void Loop (int val) {
  bool BUTTON = !Button.Read();

  if (millis() - timer >= DELAY) {
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
  }

  if (isSet[0] && isSet[1] && isSet[2] && isSet[3])
    Lock();
}

void LockedLoop (int val) {
  bool BUTTON = !Button.Read();

  if (millis() - timer >= DELAY) {
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
    if (isSet[Count - 1]){
      ENTEREDCOLORS[Count - 1] = LEDS[Count - 1].color;
      LCD.setCursor(Count * 3, 1);
      LCD.print("`");
      isSet[Count - 1] = false;
    }
  }
  
  if (!isSet[0] && !isSet[1] && !isSet[2] && !isSet[3] && isLocked && CheckArrays())
    Unlock();
  else if (!isSet[0] && !isSet[1] && !isSet[2] && !isSet[3] && isLocked && !CheckArrays())
    ShowError();
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
  isLocked = true;
  LockPin.On();
  delay(3000);
  
  LCD.setCursor(0,0);
  LCD.print("   1  2  3  4");
  LCD.setCursor(0, 1);
  LCD.print("   |  |  |  |");
}

void Unlock(){
  for (int i = 0; i < 4; ++i){
    isSet[i] = false;
  }
  isLocked = false;
  LockPin.Off();

  LCD.setCursor(0,0);
  LCD.print(" Access granted ");
  LCD.setCursor(0,1);
  LCD.print("                ");

  UnlockLCDUpdate();
}

void ShowError (){
  LCD.setCursor(0,0);
  LCD.print(" Access denied  ");
  LCD.setCursor(0,1);
  LCD.print("                ");

  LockLCDUpdate();
}

void LockLCDUpdate (){
  for (int i = 0; i < 4; ++i){
    isSet[i] = true;
  }
  isLocked = true;
  delay(3000);

  LCD.setCursor(0,0);
  LCD.print("   1  2  3  4   ");
  LCD.setCursor(0, 1);
  LCD.print("   |  |  |  |   ");
}

void UnlockLCDUpdate (){
  for (int i = 0; i < 4; ++i){
    isSet[i] = false;
  }
  isLocked = false;
  delay(3000);

  LCD.setCursor(0,0);
  LCD.print("   1  2  3  4   ");
  LCD.setCursor(0, 1);
  LCD.print("   `  `  `  `   ");
}

bool CheckArrays (){
  bool isOK[4] = {false, false, false, false};

  for (int i = 0; i < 4; ++i){
    if (ENTEREDCOLORS[i].R == UNLOCKCOLORS[i].R && ENTEREDCOLORS[i].G == UNLOCKCOLORS[i].G && ENTEREDCOLORS[i].B == UNLOCKCOLORS[i].B)
      isOK[i] = true;
  }

  if (isOK[0] && isOK[1] && isOK[2] && isOK[3])
    return true;
  else
    return false;
}

