#include "led-ring.h"

void
led_ring::setup(CRGB *leds, int num_leds)
{
	Serial.println("led_ring::setup");

	this->num_leds = num_leds;
	this->leds = leds;
}

void
led_ring::loop(void)
{
	Serial.println("led_ring::loop");
}
