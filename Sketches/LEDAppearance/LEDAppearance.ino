#define LED 12
#define LED2 2
#define LEDBOARD 13
#define BUTTON 8

unsigned long timer = 0;

bool state = false;
bool isPress = false;

int num = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEDBOARD, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  isPress = digitalRead(BUTTON);

  if (isPress && !state && millis() - timer > 150) {
    state = true;
    timer = millis();
  }

  if (!isPress && state && millis() - timer < 650) {
    state = false;
    num++;
    Serial.println(num);
  }

  if (num == 1 && millis() -  timer > 350) {
    digitalWrite(LEDBOARD, !digitalRead(LEDBOARD));
    timer = 0;
    num = 0;
  }

  if (num == 2) {
    digitalWrite(LED, !digitalRead(LED));
    timer = 0;
    num = 0;
  }

  if (isPress && !state && millis() - timer > 150) {
    state = true;
    timer = millis();
  }

  if (!isPress && state) {
    state = false;
    timer = 0;
  }

  if (millis() - timer >= 2000 && millis() - timer <= 3250){
    digitalWrite(LED2, !digitalRead(LED2));
    timer = 0;
  }
}
