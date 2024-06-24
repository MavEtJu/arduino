#ifndef __RING_SWIWRL_H__
#define __RING_SWIWRL_H__

#include "FastLED.h"
#include "led-ring.h"

class ring_swirl : public led_ring
{
public:
	ring_swirl(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);
};

#endif
