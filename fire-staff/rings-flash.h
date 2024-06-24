#ifndef __RINGS_FLASH_H__
#define __RINGS_FLASH_H__

#include "FastLED.h"
#include "led-ring.h"

class rings_flash : public led_ring
{
public:
	rings_flash(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);
};

#endif
