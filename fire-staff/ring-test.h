#ifndef __RING_TEST_H__
#define __RING_TEST_H__

#include "FastLED.h"
#include "led-ring.h"

class ring_test : public led_ring
{
public:
	void setup(CRGB *leds, int num_leds);
	void loop(void);

private:
	void loop1(void);
	void loop2(void);
};

#endif
