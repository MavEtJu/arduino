#include "rings-loop.h"

void
rings_loop::setup(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring)
{
	Serial.println("rings_loop::setup");
	led_ring::setup(leds, num_leds, number_of_rings, leds_per_ring);
}


#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
int
rings_loop::delay_value(void)
{
	static int currentdelay = 25;
	return currentdelay;
}

#define TRAIL	3
void
rings_loop::loop(void)
{
	Serial.println("ring_test::loop5");
	led_ring::loop();

	static int led = 1;
	static int ring = 0;
	static int direction = +1;

	static int leds[TRAIL] = { 1, 1, 1 };
	static int rings[TRAIL] = { 0, 0, 0 };
	static CRGB colour = CRGB( 8, 0, 0);

	// Blue markers
	CRGB c = CRGB(0, 0, 8);
	this->ring_led(0, 0, c);
	this->ring_led(0, 12, c);
	this->ring_led(1, 0, c);
	this->ring_led(1, 8, c);
	this->ring_led(2, 0, c);
	this->ring_led(2, 6, c);
	this->ring_led(3, 0, c);
	this->ring_led(3, 4, c);

	// Move spot around
	struct state *s = this->states;
	int found = 0;
	while (s->new_direction != 0) {
		if (s->current_ring == ring &&
			s->current_led == led &&
			s->current_direction == direction) {
			found = 1;
			direction = s->new_direction;
			led = s->new_led;
			ring = s->new_ring;

			if (s->swap_colour == 1) {
				int high = random(4, 9);
				int low1 = random(0, 5);
				int low2 = random(0, 5);
				switch (random(0, 3)) {
				case 0: colour = CRGB(high, low1, low2);
					break;
				case 1: colour = CRGB(low1, high, low2);
					break;
				case 2: colour = CRGB(low1, low2, high);
					break;
				}
			}
			break;
		}
		s++;
	}
	if (found == 0)
		led += direction;

	// Keep track of trailing bits
	for (int i = 0; i < TRAIL - 1; i++) {
		leds[i] = leds[i + 1];
		rings[i] = rings[i + 1];
	}
	leds[TRAIL - 1] = led;
	rings[TRAIL - 1] = ring;

	int r = colour.r;
	int g = colour.g;
	int b = colour.b;
	for (int i = TRAIL - 1; i >= 0; i--) {
		this->ring_led(rings[i], leds[i], CRGB(r, g, b));
		r >>= 1;
		g >>= 1;
		b >>= 1;
	}

}
