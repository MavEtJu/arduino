
#include "ring-test.h"

void
ring_test::setup(CRGB *leds, int num_leds)
{
	Serial.println("ring_test::setup");
	led_ring::setup(leds, num_leds);
}

void
ring_test::loop(void)
{
	this->loop2();
}

void
ring_test::loop2(void)
{
	Serial.println("ring_test::loop");
	led_ring::loop();

	static int step = 0;

	for (int i = 0; i < this->num_leds; i++) {
		switch (step % 3) {
		case 0:
			this->leds[i] = CRGB(16, 0, 0);
			break;
		case 1:
			this->leds[i] = CRGB(0, 16, 0);
			break;
		case 2:
			this->leds[i] = CRGB(0, 0, 16);
			break;
		}
	}
	step = (step + 1) % 3;

	FastLED.show();
	delay(1000);
}

void
ring_test::loop1(void)
{
	Serial.println("ring_test::loop");
	led_ring::loop();

	int wait = 100;
	static int r = 12;
	static int g = 1;

	for (int i = 0; i < this->num_leds; i++) {
		this->leds[i] = CRGB(r, g, 0);
	}
	FastLED.show();
	delay(wait);

	r += 1;
	if (r == 16) {
		r = 10;
		g++;
	}
	if (g == 3)
		g = 0;
}
