/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led[3];

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i = 0; i < 3; i++) {
    led[i] = 2 + i;
    pinMode(led[i], OUTPUT);
  }
}


void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led[i], HIGH);
    delay(200);
  }
}
