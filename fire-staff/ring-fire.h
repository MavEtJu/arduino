#ifndef __RING_FIRE_H__
#define __RING_FIRE_H__

#include "FastLED.h"
#include "led-ring.h"

class ring_fire : public led_ring
{
public:
	ring_fire(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);
};

#endif
