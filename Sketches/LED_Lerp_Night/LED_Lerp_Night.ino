#define RES_R 5
#define RES_G 6
#define RES_B 11

#include "DPL.h"

int st = 1;
int dl = 40;

using namespace DPL_SerialPort;
using namespace DPL_RGB;

RGB LED(RES_R, RES_G, RES_B, NEGATIVE);

void setup() {
  Start(9600);
  LED.Set(0, 0, 0);
}

void loop() {
  if (BUFFER_OK) {
    st = In("-d");
    dl = In();
  }

  Color target(random(0, 255), random(0, 255), random(0, 255));
  Prog_Lerp(target, st, dl);
  Out(LED, NEW_LINE);
}

void Prog_Lerp(Color targetColor, float step, int dl) {
  while (true) {
    if (LED.color.R < targetColor.R && LED.color.R + step <= 255)
      LED.color.R += step;
    if (LED.color.R > targetColor.R && LED.color.R - step >= 0)
      LED.color.R -= step;
    if (LED.color.G < targetColor.G && LED.color.G + step <= 255)
      LED.color.G += step;
    if (LED.color.G > targetColor.G && LED.color.G - step >= 0)
      LED.color.G -= step;
    if (LED.color.B < targetColor.B && LED.color.B + step <= 255)
      LED.color.B += step;
    if (LED.color.B > targetColor.B && LED.color.B - step >= 0)
      LED.color.B -= step;

    if (LED.color.R <= targetColor.R + step && LED.color.R >= targetColor.R - step && LED.color.G <= targetColor.G + step && LED.color.G >= targetColor.G - step && LED.color.B <= targetColor.B + step && LED.color.B >= targetColor.B - step)
      break;

    LED.Set(LED.color);
    delay(dl);
  }
}
