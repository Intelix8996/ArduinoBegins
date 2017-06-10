#include "DPL.h"

using namespace DPL_Pins;
using namespace DPL_SerialPort;
using namespace DPL_RGB;

Pin enc_A(11, INPUT);
Pin enc_B(12, INPUT);
Pin Button(8, INPUT_PULLUP);

RGB LED1(2,3,4, NEGATIVE);
RGB LED2(5,6,7, NEGATIVE);
RGB LED3(9,10,A1, NEGATIVE);
RGB LED4(A0, A2, A3, NEGATIVE);

int Count = 0;

unsigned long timer  = 0;

SerialPort SC(9600);

bool enc_A_prev = false;

void setup() {
  SC.Start();
  timer = millis();
  LED1.Set(0,0,0);
  LED2.Set(0,0,0);
  LED3.Set(0,0,0);
  LED4.Set(0,0,0);
}

void loop() {
  EncHandler();
  Loop(Count);
}

void Loop (int val){
  RGB LEDB(1,1,1,NEGATIVE);
  
  if (val == 1)
    LEDB = LED1;
  if (val == 2)
    LEDB = LED2;
  if (val == 3)
    LEDB = LED3;
  if (val == 4)
    LEDB = LED4;

  LEDB.Set(255,255,255);
}

void EncHandler (){
  bool A = enc_A.Read();
  bool B = enc_B.Read();
  
  if (!A && enc_A_prev && millis() - timer >= 25){
    if (B)
      --Count;
    else 
      ++Count;

    Count = constrain(Count, 1, 4);
    
    SC.Out(Count, NEW_LINE);
    timer  = millis();
  }
  
  enc_A_prev = A;
}

