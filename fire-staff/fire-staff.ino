/*
  Fire-staff
  by Edwin Groothuis
 */

#include <Arduino.h>
#include "FastLED.h"

#include "ring-test.h"
#include "ring-fire.h"
#include "ring-swirl.h"

#define DATA_PIN	3	// D3

#define NUM_RINGS	4
int leds_per_ring[NUM_RINGS] = {24, 16, 12, 8};
int num_leds = 0;

CRGB *leds;
led_ring *lr = NULL;

void
setup(void)
{
	Serial.begin(115200);
	Serial.println("setup");

	num_leds = 0;
	for (int r = 0; r < NUM_RINGS; r++) {
		num_leds += leds_per_ring[r];
	}
	leds = (CRGB *)calloc(num_leds, sizeof(CRGB));

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, num_leds);

	lr = new ring_swirl();
	lr->setup(leds, num_leds, NUM_RINGS, (int *)leds_per_ring);
}

void
loop(void)
{
	Serial.println("loop");
	CRGB black = CRGB(0, 0, 0);
	for (int led = 0; led < num_leds; led++) {
		leds[led] = black;
	}
	lr->loop();
	delay(lr->delay_value());
	FastLED.show();
}

