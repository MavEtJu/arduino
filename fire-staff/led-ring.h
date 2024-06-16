#ifndef __LED_RING_H__
#define __LED_RING_H__

#include "FastLED.h"

class led_ring
{
private:
	int *_leds_per_ring;
	int _number_of_rings;
public:
	CRGB *leds;
	int num_leds;
	int wait;

	virtual void setup(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	virtual void loop();
	virtual int delay_value();

	int leds_per_ring(int ring);
	int number_of_rings(void);

	void ring_led(int ring, int led, CRGB colour);
};

#endif
