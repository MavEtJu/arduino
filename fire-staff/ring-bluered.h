#ifndef __RING_SPINNER_H__
#define __RING_SPINNER_H__

#include "FastLED.h"
#include "led-ring.h"

#define NUMRINGS	4
struct letterdot {
	int ring;
	int ledcount;
	int *leds;
};
struct letter {
	char letter;
	struct letterdot letterdots[NUMRINGS];
};

#define LETTERCOUNT	10

class ring_bluered : public led_ring
{
	struct letter letters[LETTERCOUNT];
	int lettercounter;
public:
	ring_bluered(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring);
	void loop(void);
	int delay_value(void);
	void LETTER(char letter, int ring, int count, ...);
	void letter(char letter);
};

#endif
