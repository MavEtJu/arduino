#include "led-ring.h"

led_ring::led_ring(CRGB *leds, int num_leds, int rings, int *leds_per_ring)
{
	Serial.println("led_ring::led_ring");

	this->num_leds = num_leds;
	this->leds = leds;

	this->_number_of_rings = rings;
	this->_leds_per_ring = (int *)calloc(rings, sizeof(int));
	for (int i = 0; i < rings; i++) {
		this->_leds_per_ring[i] = leds_per_ring[i];
	}
}
led_ring::~led_ring(void)
{
	Serial.println("led_ring::~led_ring");
	free(this->_leds_per_ring);
}

void
led_ring::loop(void)
{
	Serial.println("led_ring::loop");
	this->loopcounter++;
}

int
led_ring::delay_value(void)
{
	Serial.println("led_ring::delay_value");
	return 0;
}

int
led_ring::number_of_rings(void)
{
	return this->_number_of_rings;
}

int
led_ring::leds_per_ring(int ring)
{
	return this->_leds_per_ring[ring];
}

void
led_ring::ring_led(int ring, int led, CRGB colour)
{
	int offset = 0;
	for (int r = 0; r < ring; r++) {
		offset += this->leds_per_ring(r);
	}
	this->leds[offset + led] = colour;
}

/* https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory */
int
freeRam(void)
{
#ifdef SIMULATOR
    return 2048;
#else
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
#endif
}

