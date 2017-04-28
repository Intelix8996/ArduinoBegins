#define LED 12
#define LED2 2
#define LEDBOARD 13
#define BUTTON 8

unsigned long timer = 0;

bool state = false;
bool isPress = false;

int num = 0;
int mode = 0;

String modes[4] = { "Sleep", "Single-click LED", "Double-click LED", "Hold LED"};

void StartupBlink (int dl, int times){
  for (int i = 0; i < times; ++i){
    digitalWrite(LEDBOARD, HIGH);
    delay(dl);
    digitalWrite(LEDBOARD, LOW);
    delay(dl);
    digitalWrite(LED, HIGH);
    delay(dl);
    digitalWrite(LED, LOW);
    delay(dl);
    digitalWrite(LED2, HIGH);
    delay(dl);
    digitalWrite(LED2, LOW);
    delay(dl);
  }
}

void Blink (int LEDnum, int dl){
  if (LEDnum == 1){
    digitalWrite(LEDBOARD, HIGH);
    delay(dl);
    digitalWrite(LEDBOARD, LOW);
  }
  if (LEDnum == 2){
      digitalWrite(LED, HIGH);
      delay(dl);
      digitalWrite(LED, LOW);
   }
   if (LEDnum == 3){
      digitalWrite(LED2, HIGH);
      delay(dl);
      digitalWrite(LED2, LOW);
   }
}

void setup() {
  Serial.begin(9600);
  Serial.println("System mode: Starting up");
  
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEDBOARD, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  StartupBlink(50, 20);
  Serial.println("System mode: Ready");
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
  }

  if (num == 3) {
    timer = 0;
    num = 0;
    mode++;

    if (mode >= 4)
      mode = 1;

    Serial.print("System mode: ");
    Serial.print(mode);
    Serial.print(" (");
    Serial.print(modes[mode]);
    Serial.println(") ");

    Blink(mode, 1500);
  }

  if (mode == 1 && num == 1 && millis() -  timer > 350) {
    digitalWrite(LEDBOARD, !digitalRead(LEDBOARD));
    timer = 0;
    num = 0;
  }

  if (mode == 2 && num == 2 && millis() -  timer > 550) {
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

  if (mode == 3 && millis() - timer >= 2000 && millis() - timer <= 3250){
    num = 0;
    digitalWrite(LED2, !digitalRead(LED2));
    timer = 0;
  }
}
