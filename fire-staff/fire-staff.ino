/*
  Fire-staff
  by Edwin Groothuis
 */

#include <Arduino.h>
#include "FastLED.h"

#include "ring-test.h"
#include "ring-fire.h"
#include "ring-swirl.h"
#include "rings-loop.h"
#include "rings-flash.h"

#define DATA_PIN_CIRCLE	3	// D3
#define DATA_PIN_TOWER	4	// D3

#define NUM_RINGS	4
int leds_per_ring_tower[NUM_RINGS] = {24, 16, 12, 8};
int leds_per_ring_circle[NUM_RINGS] = {24, 16, 12, 8};
int num_leds_tower = 0;
int num_leds_circle = 0;

CRGB *leds_tower;
CRGB *leds_circle;
led_ring *lr_tower = NULL;
led_ring *lr_circle = NULL;

void
setup(void)
{
	Serial.begin(115200);
	Serial.println("setup");
	//Serial.end();

	num_leds_tower = 0;
	for (int r = 0; r < NUM_RINGS; r++) {
		num_leds_tower += leds_per_ring_tower[r];
	}
	leds_tower = (CRGB *)calloc(num_leds_tower, sizeof(CRGB));

	num_leds_circle = 0;
	for (int r = 0; r < NUM_RINGS; r++) {
		num_leds_circle += leds_per_ring_circle[r];
	}
	leds_circle = (CRGB *)calloc(num_leds_circle, sizeof(CRGB));

//	FastLED.addLeds<NEOPIXEL, DATA_PIN_CIRCLE>(leds_circle, num_leds_circle);
	FastLED.addLeds<NEOPIXEL, DATA_PIN_TOWER>(leds_tower, num_leds_tower);

//	lr_circle = new ring_fire();
//	lr_circle->setup(leds_circle, num_leds_circle, NUM_RINGS, (int *)leds_per_ring_circle);
	lr_tower = new rings_flash();
	lr_tower->setup(leds_tower, num_leds_tower, NUM_RINGS, (int *)leds_per_ring_tower);
}

void
loop(void)
{
	Serial.println("loop");
	Serial.println(millis());
	static int loopcounter = 0;

	if (lr_tower->finished) {
		free(lr_tower);
		lr_tower = new rings_loop();
		lr_tower->setup(leds_tower, num_leds_tower, NUM_RINGS, (int *)leds_per_ring_tower);
	}

	int current_second = millis() / 1000;
	int previous_second = 0;
	if (current_second != previous_second && current_second % 600 == 0) {
		free(lr_tower);
		lr_tower = new rings_flash();
		lr_tower->setup(leds_tower, num_leds_tower, NUM_RINGS, (int *)leds_per_ring_tower);
	}
	previous_second = current_second;

	CRGB black = CRGB(0, 0, 0);
	for (int led = 0; led < num_leds_circle; led++) {
		leds_circle[led] = black;
	}
	for (int led = 0; led < num_leds_tower; led++) {
		leds_tower[led] = black;
	}
//	lr_circle->loop();
	lr_tower->loop();
	delay(lr_tower->delay_value());

	loopcounter++;

	FastLED.show();
}

