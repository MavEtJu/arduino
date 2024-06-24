#ifndef __LED_RING_H__
#define __LED_RING_H__

#include "FastLED.h"

enum class_type {
	LED_RING	= 0,
	LED_RING_TEST,
	LED_RINGS_FLASH,
	LED_RINGS_LOOP,
	LED_RING_FIRE,
	LED_RING_SWIRL,
};

class led_ring
{
private:
	int *_leds_per_ring;
	int _number_of_rings;
public:
	led_ring(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	virtual ~led_ring(void);

	int class_type = LED_RING;

	CRGB *leds;
	int num_leds;
	int wait;

	// If the sequence of events for this animation is finished
	int finished = 0;

	unsigned int loopcounter = 0;

	virtual void loop();
	virtual int delay_value();

	int leds_per_ring(int ring);
	int number_of_rings(void);

	void ring_led(int ring, int led, CRGB colour);
};

int freeRam(void);

#endif
