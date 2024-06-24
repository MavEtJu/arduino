#include "ring-swirl.h"

ring_swirl::ring_swirl(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring) : led_ring(leds, num_leds, number_of_rings, leds_per_ring)
{
	Serial.println("ring_swirl::ring_swirl");
	this->class_type = LED_RING_SWIRL;
}

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
int
ring_swirl::delay_value(void)
{
	static int currentdelay = 150;
	if (this->loopcounter % 24 == 0) {
		currentdelay += 10 * random(-1, 2);
		currentdelay = MIN(200, MAX(50, currentdelay));
	}
	return currentdelay;
}

void
ring_swirl::loop(void)
{
	Serial.println("ring_swirl::loop");
	led_ring::loop();

	static int step = 0;

	CRGB c1 = CRGB(8, 0, 0);
	CRGB c2 = CRGB(0, 8, 0);
	CRGB c3 = CRGB(0, 0, 8);
	CRGB c4 = CRGB(8, 0, 8);
	for (int ring = 0; ring < this->number_of_rings(); ring++) {
		int lpr = this->leds_per_ring(ring);
		this->ring_led(ring, (step + 0          ) % lpr, c1);
		this->ring_led(ring, (step + lpr / 2 + 0) % lpr, c1);
		this->ring_led(ring, (step + 2          ) % lpr, c2);
		this->ring_led(ring, (step + 2 + lpr / 2) % lpr, c2);
		this->ring_led(ring, (step + 4          ) % lpr, c3);
		this->ring_led(ring, (step + 4 + lpr / 2) % lpr, c3);
		this->ring_led(ring, (step + 6          ) % lpr, c4);
		this->ring_led(ring, (step + 6 + lpr / 2) % lpr, c4);
	}

	step = step + 1;
}
