/*
  Fire-staff
  by Edwin Groothuis
 */

#include <Arduino.h>
#include "FastLED.h"

#include "ring-test.h"
#include "ring-fire.h"

#define DATA_PIN	3	// D3
#define NUM_LEDS 24 + 16 + 12 + 8

CRGB leds[NUM_LEDS];
led_ring *lr = NULL;

void
setup(void)
{
	Serial.begin(115200);
	Serial.println("setup");

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

	lr = new ring_fire();
	lr->setup(leds, NUM_LEDS);
}

void
loop(void)
{
	Serial.println("loop");
	lr->loop();
}

