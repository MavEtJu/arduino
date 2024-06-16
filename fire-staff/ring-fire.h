#ifndef __RING_FIRE_H__
#define __RING_FIRE_H__

#include "FastLED.h"
#include "led-ring.h"

class ring_fire : public led_ring
{
public:
	void setup(CRGB *leds, int num_leds);
	void loop(void);
};

#endif
