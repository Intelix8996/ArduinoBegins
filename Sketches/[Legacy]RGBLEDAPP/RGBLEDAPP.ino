#define RES_R 10
#define RES_G 6
#define RES_B 5

#include "DPL_Legacy.h"

using namespace DPL_DigitalPins;
using namespace DPL_SerialPort;
using namespace DPL_RGB;

int val = 0;
int dl = 500;

RGB LED(10,6,5,NEGATIVE);

void setup() {
  //pinMode(RES_R, OUTPUT);
  //pinMode(RES_G, OUTPUT);
  //pinMode(RES_B, OUTPUT);
  Start(9600);
}

void loop() {
  LED.Set(random(0, 255), random(0, 255), random(0, 255));

  if (BUFFER_OK)
    dl = In();

  Out("LED", LED, NEW_LINE);
  delay(dl);
  /*
  byte R = random(0, 255);
  byte G = random(0, 255);
  byte B = random(0, 255);

  if (BUFFER_OK)
    dl = In();

  analogWrite(RES_R, R);
  analogWrite(RES_G, G);
  analogWrite(RES_B, B);
  Out("R: " + S(R) + " G: " + S(G) + " B: " + S(B) + " Delay: " + S(dl), NEW_LINE);
  delay(dl);*/
  
  /*
  if (BUFFER_OK){
    val = In();
    Out(val, NEW_LINE);
  }

  if (val equal 1){
    Off(RES_R);
    On(RES_G);
    On(RES_B);
  }
   if (val equal 2){
    On(RES_R);
    Off(RES_G);
    On(RES_B);
  }
   if (val equal 3){
    On(RES_R);
    On(RES_G);
    Off(RES_B);
  }
  if (val equal 4){
    Off(RES_R);
    Off(RES_G);
    Off(RES_B);
  }
  else{
    On(RES_R);
    On(RES_G);
    On(RES_B);
  }*/
    
  
  /*
  val = analogRead(RES);
  val = constrain(val, 650, 950);
  val = map(val, 650, 950, 0, 255);
  val = 255 - val;
  analogWrite(LED2, val);*/
}
