
#include "ring-test.h"

void
ring_test::setup(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring)
{
	Serial.println("ring_test::setup");
	led_ring::setup(leds, num_leds, number_of_rings, leds_per_ring);
}

void
ring_test::loop(void)
{
	this->loop4();
}

int
ring_test::delay_value(void)
{
	return 100;
}

void
ring_test::line_horizontal(int lineno, CRGB colour)
{
}

void
ring_test::line_vertical(int lineno, CRGB colour)
{
}

void
ring_test::line_angle(int lineno, CRGB colour)
{
}

void
ring_test::ring_led(int ring, int led, CRGB colour)
{
	int offset = 0;
	for (int r = 0; r < ring; r++) {
		offset += this->leds_per_ring(r);
	}
	this->leds[offset + led] = colour;
}

void
ring_test::loop4(void)
{
	Serial.println("ring_test::loop4");
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

void
ring_test::loop3(void)
{
	Serial.println("ring_test::loop3");
	led_ring::loop();

	static int step = 0;

	CRGB red = CRGB(8, 0, 0);
	for (int i = 0; i < (step % this->num_leds); i++) {
		this->leds[i] = red;
	}
	step = step + 1;
}

void
ring_test::loop2(void)
{
	Serial.println("ring_test::loop2");
	led_ring::loop();

	static int step = 0;

	CRGB colour;
	switch (step % 3) {
	case 0:
		colour = CRGB((step / 3) % 16, 0, 0);
		break;
	case 1:
		colour = CRGB(0, (step / 3) % 16, 0);
		break;
	case 2:
		colour = CRGB(0, 0, (step / 3) % 16);
		break;
	}

	for (int i = 0; i < this->num_leds; i++) {
		this->leds[i] = colour;
	}
	step = step + 1;
}

void
ring_test::loop1(void)
{
	Serial.println("ring_test::loop1");
	led_ring::loop();

	static int r = 12;
	static int g = 1;

	CRGB colour = CRGB(r, g, 0);
	for (int i = 0; i < this->num_leds; i++) {
		this->leds[i] = colour;
	}

	r += 1;
	if (r == 16) {
		r = 10;
		g++;
	}
	if (g == 3)
		g = 0;
}
