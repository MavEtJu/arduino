/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led[8] = { 13, 12, 11, 10, 9, 8, 7, 2};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i = 0; i < 8; i++) {
    pinMode(led[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop_walk() {
  int df = 100;
  for (int i = 0; i < 8; i++) {
    digitalWrite(led[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(df);               // wait for a second
    digitalWrite(led[i], LOW);    // turn the LED off by making the voltage LOW
    delay(df);               // wait for a second
  }
}

void loop_fill1() {
  int df = 100;
  for (int i = 0; i < 8; i++) {
    digitalWrite(led[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(df);               // wait for a second
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(led[i], LOW);   // turn the LED on (HIGH is the voltage level)
    delay(df);               // wait for a second
  }
}

void loop_fill2() {
  int df = 100;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < i + 1; j++) {
      digitalWrite(led[j], HIGH);
      delay(df);
    }
    for (int j = i + 1; j >= 0; j--) {
      digitalWrite(led[j], LOW);
      delay(df);
    }
  }
}

void sleep() {
  delay(500);
}


void loop() {
  loop_walk();
  sleep();
  loop_fill1();
  sleep();
  loop_fill2();
}
