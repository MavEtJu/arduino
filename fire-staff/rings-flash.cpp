#include "rings-flash.h"

void
rings_flash::setup(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring)
{
	Serial.println("rings_flash::setup");
	led_ring::setup(leds, num_leds, number_of_rings, leds_per_ring);

	this->class_type = LED_RINGS_FLASH;
}

int
rings_flash::delay_value(void)
{
	return 25;
}

#define TRAIL	3
void
rings_flash::loop(void)
{
	Serial.println("rings_flash::loop");
	led_ring::loop();

	// Run it for only a second.
	if (this->loopcounter == 40)
		this->finished = true;

	static CRGB colour = CRGB( 8, 8, 4);

	if (random(0, 4) == 0) {
		for (int i = 0; i < this->num_leds; i++) {
			this->leds[i] = colour;
		}
	}

	// Blue markers
	static CRGB c = CRGB(0, 8, 8);
	this->ring_led(0, 0, c);
	this->ring_led(0, 12, c);
	this->ring_led(1, 0, c);
	this->ring_led(1, 8, c);
	this->ring_led(2, 0, c);
	this->ring_led(2, 6, c);
	this->ring_led(3, 0, c);
	this->ring_led(3, 4, c);
}
