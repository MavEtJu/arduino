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
	LED_RING_BLUERED,
	LED_RING_SPINNER,
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
	int ring_led_to_offset(int ring, int led);
	int offset_to_led(int offset);
	int offset_to_ring(int offset);
};

int freeRam(void);

#endif
