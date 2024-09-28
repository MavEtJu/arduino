#ifndef __RING_FIRE_H__
#define __RING_FIRE_H__

#include "FastLED.h"
#include "led-ring.h"

class ring_bluered : public led_ring
{
public:
	ring_bluered(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);
};

#endif
