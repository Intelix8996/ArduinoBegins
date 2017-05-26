#define BUZZER 12

#include "DPL_Legacy.h"

using namespace DPL_SerialPort;

int Freq = 500;

void setup() {
  Start(9600);
  pinMode(BUZZER, OUTPUT);
  Out("System Ready!", NEW_LINE);
  tone(BUZZER, Freq);
}

void loop() {
  if (BUFFER_OK) {
    Freq = In();
    Out("\nNew Freq: " + S(Freq), NEW_LINE);
    noTone(BUZZER);
    tone(BUZZER, Freq);
  }
}

/*
#define BUZZER 3
#define high digitalWrite(BUZZER, HIGH)
#define low digitalWrite(BUZZER, LOW);

float Delay = 1;
unsigned long long timer = 1;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  timer = millis();
  Serial.println ("System Ready!");
}

void loop() {
  if (Serial.available() > 0) {
    Delay = Serial.parseFloat();
    Serial.print("New delay: ");
    Serial.print(Delay);
    Serial.println("ms");
  }
  /*
  if (millis() - timer == Delay)
    high;
  
  if (millis() - timer >= (Delay * 2)){
    low;
    timer = millis();
  }
  
  high;
  delay(Delay);
  low;
  delay(Delay);
}
*/
