#include "ring-spinner.h"

const byte RED = 16;

ring_spinner::ring_spinner(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring) : led_ring(leds, num_leds, number_of_rings, leds_per_ring)
{
	Serial.println("ring_spinner::ring_spinner");
	this->class_type = LED_RING_SPINNER;
}


int
ring_spinner::delay_value(void)
{
	return 100;
}

void
ring_spinner::loop(void)
{
	Serial.println("ring_spinner::loop");
	led_ring::loop();

	for (int i = 0; i < num_leds; i++) {
		CRGB colour = CRGB(random(4, 15), 0, 0);
		leds[i] = colour;
	}
//	colour = CRGB(10, 0, 5);
//	for (int i = 0; i < leds_per_ring(1); i++) {
//		leds[ring_led_to_offset(1, i)] = colour;
//	}

	if (loopcounter % 5 == 0) {
	for (int r = 0; r < number_of_rings(); r++) {
		for (int i = 0; i < leds_per_ring(r); i += leds_per_ring(r) / 4) {
			CRGB c = leds[ring_led_to_offset(r, i)];
			c.g = 1;
			leds[ring_led_to_offset(r, i)] = c;
		}
	}
	}

	FastLED.show();
}
