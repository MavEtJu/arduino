
#include "ring-fire.h"

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

/******************CODE*****************/
/**************DO NOT TOUCH*************/
/*********unless you really need********/

const byte RED = 16;

float SineEaseOut(float p);
float QuadraticEaseInOut(float p);
float CubicEaseInOut(float p);

ring_fire::ring_fire(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring) : led_ring(leds, num_leds, number_of_rings, leds_per_ring)
{
	Serial.println("ring_fire::ring_fire");
	this->class_type = LED_RING_FIRE;
}


int
ring_fire::delay_value(void)
{
	return 100;
}

void
ring_fire::loop(void)
{
	Serial.println("ring_fire::loop");
	led_ring::loop();

	static int tick = 100;

	unsigned int time = millis();

	float rfactor = 1.0;
	float gfactor = 0.1;
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
		float yellow = vi *((MAX_VARIATION - MIN_VARIATION)*v + MIN_VARIATION);

		leds[i] = CRGB(red * rfactor, red * gfactor, red * bfactor);
	}
	FastLED.show();
}

float CubicEaseInOut(float p)
{
	if (p < 0.5) {
		return 4 * p * p * p;
	} else {
		float f = ((2 * p) - 2);
		return 0.5 * f * f * f + 1;
	}
}

float QuadraticEaseInOut(float p)
{
	if (p < 0.5) {
		return 2 * p * p;
	} else {
		return (-2 * p * p) + (4 * p) - 1;
	}
}

float SineEaseOut(float p)
{
	return sin(p * M_PI_2);
}

/*
// the loop function runs over and over again forever
void loop2() {
	static int loopcounter = 0;
	unsigned int i;
	uint32_t c;
	int v = 2; // random();
	switch (++loopcounter % 8) {
	case 0:
		c = strip.Color(v, 0, 0);
		break;
	case 1:
		c = strip.Color(0, v, 0);
		break;
	case 2:
		c = strip.Color(0, 0, v);
		break;
	case 3:
		c = strip.Color(v, v, 0);
		break;
	case 4:
		c = strip.Color(0, v, v);
		break;
	case 5:
		c = strip.Color(v, 0, v);
		break;
	case 6:
		c = strip.Color(v, v, v);
		break;
	case 7:
		c = strip.Color(0, 0, 0);
		break;
	}

	for (i = 0; i < strip.numPixels(); i++) {
		Serial.println(i);
		strip.setPixelColor(i, c);
		strip.show();
		strip.setPixelColor(i, black);
	}
}
*/
