#ifndef __RING_TEST_H__
#define __RING_TEST_H__

#include "FastLED.h"
#include "led-ring.h"

class ring_test : public led_ring
{
public:
	void setup(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);

private:
	void loop1(void);
	void loop2(void);
	void loop3(void);
	void loop4(void);
	void ring_led(int ring, int led, CRGB colour);
	void line_horizontal(int lineno, CRGB colour);
	void line_vertical(int lineno, CRGB colour);
	void line_angle(int lineno, CRGB colour);
};

#endif
