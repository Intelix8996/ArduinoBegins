#define LED 12
#define LED2 2
#define LEDBOARD 13
#define BUTTON 8

unsigned long timer = 0;
<<<<<<< HEAD
unsigned long sleepTimer = 0;

bool state = false;
bool isPress = false;
bool sleep = true;
=======

bool state = false;
bool isPress = false;
>>>>>>> experimental

int num = 0;
int mode = 0;

String modes[4] = { "Sleep", "Single-click LED", "Double-click LED", "Hold LED"};

<<<<<<< HEAD
void offLEDS () {
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LEDBOARD, LOW);
}

void StartupBlink (int dl, int times) {
  for (int i = 0; i < times; ++i) {
=======
void StartupBlink (int dl, int times){
  for (int i = 0; i < times; ++i){
>>>>>>> experimental
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

<<<<<<< HEAD
void Blink (int LEDnum, int dl) {
  if (LEDnum == 1) {
=======
void Blink (int LEDnum, int dl){
  if (LEDnum == 1){
>>>>>>> experimental
    digitalWrite(LEDBOARD, HIGH);
    delay(dl);
    digitalWrite(LEDBOARD, LOW);
  }
<<<<<<< HEAD
  if (LEDnum == 2) {
    digitalWrite(LED, HIGH);
    delay(dl);
    digitalWrite(LED, LOW);
  }
  if (LEDnum == 3) {
    digitalWrite(LED2, HIGH);
    delay(dl);
    digitalWrite(LED2, LOW);
  }
=======
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
>>>>>>> experimental
}

void setup() {
  Serial.begin(9600);
  Serial.println("System mode: Starting up");
<<<<<<< HEAD

=======
  
>>>>>>> experimental
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEDBOARD, OUTPUT);
  pinMode(LED2, OUTPUT);
<<<<<<< HEAD

  StartupBlink(50, 20);
  delay(500);
  isPress = 0;
=======
  
  StartupBlink(50, 20);
>>>>>>> experimental
  Serial.println("System mode: Ready");
}

void loop() {
  isPress = digitalRead(BUTTON);

<<<<<<< HEAD
  if (sleep) {
    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state && millis() - timer < 650) {
      state = false;
      num++;
    }

    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state) {
      state = false;
      timer = 0;
    }

    if (num == 1 && millis() -  timer > 350) {
      timer = 0;
      num = 0;
    }

    if (num == 2 && millis() -  timer > 550) {
      timer = 0;
      num = 0;
    }

    if (millis() - timer >= 1000 && millis() - timer <= 2460) {
      num = 0;
      timer = 0;
    }
    if (millis() - sleepTimer >= 5000 && millis() - sleepTimer <= 6250) {
      sleep = !sleep;
      num = 0;
      sleepTimer = 0;
      mode = 1;
      Serial.println("Entering normal mode...");
    }
  }
  else if (!sleep) {
    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state && millis() - timer < 650) {
      state = false;
      num++;
    }

    if (isPress && !state && millis() - timer > 150) {
      state = true;
      timer = millis();
      sleepTimer = millis();
    }

    if (!isPress && state) {
      state = false;
      timer = 0;
    }

    if (num == 3) {
      offLEDS();
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

    if (mode == 1) {
      if (num == 1 && millis() -  timer > 350) {
        digitalWrite(LEDBOARD, !digitalRead(LEDBOARD));
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (num == 2 && millis() -  timer > 550) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (millis() - timer >= 1000 && state && millis() - timer <= 2460) {
        num = 0;
        timer = 0;
      }
      if (millis() - sleepTimer >= 5000 && state && millis() - sleepTimer <= 6250) {
        sleep = !sleep;
        num = 0;
        sleepTimer = 0;
        mode = 1;
        offLEDS();
        Serial.println("Entering sleep mode...");
      }
    }
    if (mode == 2) {
      if (num == 1 && millis() -  timer > 350) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (num == 2 && millis() -  timer > 550) {
        digitalWrite(LED, !digitalRead(LED));
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (millis() - timer >= 1000 && state && millis() - timer <= 2460) {
        num = 0;
        timer = 0;
      }
      if (millis() - sleepTimer >= 5000 && state && millis() - sleepTimer <= 6250) {
        sleep = !sleep;
        num = 0;
        sleepTimer = 0;
        mode = 1;
        offLEDS();
        Serial.println("Entering sleep mode...");
      }
    }
    if (mode == 3) {
      if (num == 1 && millis() -  timer > 350) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (num == 2 && millis() -  timer > 550) {
        timer = 0;
        sleepTimer = 0;
        num = 0;
      }

      if (millis() - timer >= 1000 && state && millis() - timer <= 2460) {
        digitalWrite(LED2, !digitalRead(LED2));
        num = 0;
        timer = 0;
      }
      if (millis() - sleepTimer >= 5000 && state && millis() - sleepTimer <= 6250) {
        sleep = !sleep;
        num = 0;
        sleepTimer = 0;
        mode = 1;
        offLEDS();
        Serial.println("Entering sleep mode...");
      }
    }
=======
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
>>>>>>> experimental
  }
}
