
#include "ring-bluered.h"
#include "fire-effects.h"

// The variation in yellow color to create the fire effect, define the interval where the color can change.
#define MIN_VARIATION 0
#define MAX_VARIATION 30

// Value must be between 0 & 1.
// If you never want a LED to be completly off, put 0.1 to min
#define MIN_INTENSITY 0.1
#define MAX_INTENSITY 1.0

// Speed for variations, higher is slower
#define NOISE_SPEED_COLOR 5
#define NOISE_SPEED_INTENSITY 3

const byte RED = 16;

ring_bluered::ring_bluered(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring) : led_ring(leds, num_leds, number_of_rings, leds_per_ring)
{
	Serial.println("ring_bluered::ring_bluered");
	this->class_type = LED_RING_BLUERED;
}

int
ring_bluered::delay_value(void)
{
	return 100;
}

#define MAX(a, b) ((a) > (b)) ? (a) : (b)

void
ring_bluered::loop(void)
{
	Serial.println("ring_bluered::loop");
	led_ring::loop();

	static int tick = 100;

	unsigned int time = millis();

	float rfactor = 1.0;
	float gfactor = 0.0;
	float bfactor = 0.0;
	tick++;

	for (int i = 0; i < this->num_leds; i++) {
		// adjust the mult and divide to change the global effect
		// will be added to advanced settings later
		double n = inoise8(i * 250, (time + i) / NOISE_SPEED_COLOR);
		double ni = inoise8(i * 500, (time + i) / NOISE_SPEED_INTENSITY);

		// You can change the easing function here
		// Used to avoid a linear effect and give a more natural curve.
		float v = QuadraticEaseInOut(n / 255);
		float vi = QuadraticEaseInOut(ni / 255);

		vi = (MAX_INTENSITY - MIN_INTENSITY) * v + MIN_INTENSITY;
		float red = vi * (RED * v);

		leds[i] = CRGB(red * rfactor, red * gfactor, red * bfactor);
	}

	CRGB c;
	c = leds[ring_led_to_offset(0,  0)]; c.g = MAX(c.r / 10, 1); ring_led(0,  0, c);
	c = leds[ring_led_to_offset(1,  0)]; c.g = MAX(c.r / 10, 1); ring_led(1,  0, c);
	c = leds[ring_led_to_offset(2,  0)]; c.g = MAX(c.r / 10, 1); ring_led(2,  0, c);
	c = leds[ring_led_to_offset(3,  0)]; c.g = MAX(c.r / 10, 1); ring_led(3,  0, c);

	FastLED.show();
}
