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
  }*/
  
  high;
  delay(Delay);
  low;
  delay(Delay);
}
