#ifndef __LED_RING_H__
#define __LED_RING_H__

#include "FastLED.h"

class led_ring
{
public:
	CRGB *leds;
	int num_leds;

	virtual void setup(CRGB *leds, int num_leds);
	virtual void loop();
};

#endif
