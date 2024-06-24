/*
  Fire-staff
  by Edwin Groothuis
 */

#include <Arduino.h>
#include "FastLED.h"

#include "rings-loop.h"
#include "rings-flash.h"

#define DATA_PIN	4	// D4

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
	Serial.end();
	randomSeed(analogRead(0));

	num_leds = 0;
	for (int r = 0; r < NUM_RINGS; r++) {
		num_leds += leds_per_ring[r];
	}
	leds = (CRGB *)calloc(num_leds, sizeof(CRGB));

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, num_leds);

	lr = new rings_flash(leds, num_leds, NUM_RINGS, (int *)leds_per_ring);
}

void
loop(void)
{
	Serial.println("loop");
	static int loopcounter = 0;

	if (lr->finished) {
		delete lr;
		lr = new rings_loop(leds, num_leds, NUM_RINGS, (int *)leds_per_ring);
	}


	int current_second = millis() / 1000;
	int previous_second = 0;
	if (current_second != previous_second) {
		if (current_second % 10 == 0 && lr->class_type != LED_RINGS_FLASH) {
			delete lr;
			lr = new rings_flash(leds, num_leds, NUM_RINGS, (int *)leds_per_ring);
		}
		previous_second = current_second;
	}

	for (int led = 0; led < num_leds; led++) {
		leds[led] = CRGB::Black;
	}
	lr->loop();
	FastLED.show();

	delay(lr->delay_value());
	loopcounter++;
}

