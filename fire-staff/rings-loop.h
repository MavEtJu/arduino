#ifndef __RINGS_LOOP_H__
#define __RINGS_LOOP_H__

#include "FastLED.h"
#include "led-ring.h"

struct state {
	int current_ring;
	int current_led;
	int current_direction;
	int new_direction;
	int new_ring;
	int new_led;

	int swap_colour;
	int more_choices;
};

class rings_loop : public led_ring
{
private:
	struct state states[15] = {
		// Going down
		{ 0, 11, +1,	-1, 1, 15,	0, 2 },
		{ 0, 11, +1,	+1, 0, 13,	0, 0 },
		{ 1,  9, -1,	+1, 2,  1,	0, 2 },
		{ 1,  9, -1,	-1, 1,  7,	0, 0 },
		{ 2,  5, +1,	-1, 3,  7,	0, 2 },
		{ 2,  5, +1,	+1, 2,  7,	0, 0 },

		// When at the bottom, skip the blue dot
		{ 3,  5, -1,	-1, 3,  3,	0, 0 },

		// Going up
		{ 3,  1, -1,	+1, 2,  7,	0, 2 },
		{ 3,  1, -1,	-1, 3,  7,	0, 0 },
		{ 2, 11, +1,	-1, 1,  7,	0, 2 },
		{ 2, 11, +1,	+1, 2, 11,	0, 0 },
		{ 1,  1, -1,	+1, 0, 13,	0, 2 },
		{ 1,  1, -1,	-1, 1, 15,	0, 0 },

		// When at the top, skip the blue dot
		{ 0, 23, +1,	+1, 0,  1,	1, 0 },

		{ 0,  0,  0,	 0, 0,  0,	0, 0 }
	};

public:
	void setup(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);
};

#endif
