#include "DPL.h"
#include "SharpIR.h"

using namespace DPL_Pins;
using namespace DPL_SerialPort;

#define MODEL 20150

Pin IN(0, INPUT);
Pin IN2(2, INPUT);
Pin BUZZ(9, OUTPUT);

SharpIR IR(IN2.pinNumber, MODEL);

byte Value = 0;

byte distPri = 0;
byte lightPri = 0;

byte deltaDist = 0;
byte deltaLight = 0;

SerialPort SC(9600);

void setup() {
  SC.Start();
  distPri = IR.distance();
  lightPri = IN.readPWM();
}

void loop() {
  deltaDist = distPri - IR.distance();
  deltaLight = lightPri - IN.readPWM();
  SC.Send(S(deltaDist) + " "  + S(deltaLight), NEW_LINE);

  deltaLight = constrain(deltaLight, 50, 255);
  deltaDist = constrain(deltaDist, 15, 255);

  if (deltaDist > 35 && deltaLight > 80)
    Alarm();
}

void Alarm (){
  tone(9, 2500, 500);
  int timer = millis();
  if (millis() - timer >= 500)
  {
    tone(9, 1000, 500);
    timer = millis();
  }
}

