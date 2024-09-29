#include "ring-bluered.h"

const byte RED = 16;

void
ring_bluered::LETTER(char letter, int ring, int count, ...)
{
	int letterno = -1;
	for (int i = 0; i < LETTERCOUNT; i++) {
		if (this->letters[i].letter == letter) {
			letterno = i;
			break;
		}
	}
	if (letterno == -1)
		letterno = this->lettercounter++;

	Serial.println("Letter");
	Serial.println(letter);
	Serial.println("Index");
	Serial.println(letterno);

	this->letters[letterno].letter = letter;
	this->letters[letterno].letterdots[ring].ring = ring;
	this->letters[letterno].letterdots[ring].ledcount = count;

	va_list argptr;
	va_start(argptr, count);
	this->letters[letterno].letterdots[ring].leds = (int *)calloc(count, sizeof(int));
	for (int i = 0; i < count; i++) {	
		this->letters[letterno].letterdots[ring].leds[i] = va_arg(argptr, int);
	}

	va_end(argptr);
}

ring_bluered::ring_bluered(CRGB *leds, int num_leds, int number_of_rings, int *leds_per_ring) : led_ring(leds, num_leds, number_of_rings, leds_per_ring)
{
	Serial.println("ring_bluered::ring_bluered");
	this->class_type = LED_RING_SPINNER;

	for (int i = 0; i < LETTERCOUNT; i++) {
		this->letters[i].letter = '\0';
	}

	for (int i = 0; i < LETTERCOUNT; i++) {
		this->letters[i].letter = '\0';
		for (int j = 0; j < NUMRINGS; j++) {
			this->letters[i].letterdots[j].ring = 0;
			this->letters[i].letterdots[j].ledcount = 0;
			this->letters[i].letterdots[j].leds = NULL;
		}
	}
	this->lettercounter = 0;

	// WELL HIDDEN
	// WELHIDN

	LETTER('W', 0,12, 20, 19, 18, 17, 16, 15, 10,  9,  8,  7,  6,  5);
	LETTER('W', 1, 2,  7, 10);
	LETTER('W', 2, 2,  5,  7);
	LETTER('W', 3, 1,  4);

	LETTER('E', 0, 4, 23,  0,  1,  2);
	LETTER('E', 1, 2, 15,  5);
	LETTER('E', 2, 5, 11,  6,  5,  4,  2);
	LETTER('E', 3, 5,  6,  5,  7,  0,  1);

	LETTER('L', 0, 1, 23);
	LETTER('L', 1, 2, 15,  5);
	LETTER('L', 2, 4, 11,  6,  5,  4);
	LETTER('L', 3, 3,  6,  5,  7);

	LETTER('H', 0, 2, 23,  2);
	LETTER('H', 1, 3, 15,  6,  2);
	LETTER('H', 2, 5, 11,  4,  7,  3,  2);
	LETTER('H', 3, 5,  6,  5,  7,  0,  1);

	LETTER('I', 0, 6,  0, 12,  1, 23, 11, 13);
	LETTER('I', 1, 2,  0,  8);
	LETTER('I', 2, 2,  0,  6);
	LETTER('I', 3, 2,  0,  4);

	LETTER('D', 0, 5, 10,  2, 13, 11, 12, 14);
	LETTER('D', 1, 3,  6,  9,  2);
	LETTER('D', 2, 4,  7,  2,  3,  4);
	LETTER('D', 3, 2,  4,  3);

	LETTER('N', 0, 4, 21, 15,  9,  3);
	LETTER('N', 1, 8, 14,  6, 13, 12, 11,  5,  4,  3);
	LETTER('N', 2, 2, 10,  4);
	LETTER('N', 3, 2,  7,  3);
}


int
ring_bluered::delay_value(void)
{
	return 400;
}

void
ring_bluered::loop(void)
{
	Serial.println("ring_bluered::loop");
	led_ring::loop();


	for (int i = 0; i < num_leds; i++) {
		CRGB colour = CRGB(0, random(3, 10), random(1, 5));
		leds[i] = colour;
	}

	int now = this->loopcounter % 50;
	Serial.println(now);
	switch (now) {
	case  4: letter('W'); break;
	case  8: letter('E'); break;
	case 12: letter('L'); break;
	case 16: letter('L'); break;
	case 20: letter('H'); break;
	case 24: letter('I'); break;
	case 28: letter('D'); break;
	case 32: letter('D'); break;
	case 36: letter('E'); break;
	case 40: letter('N'); break;
	}
}

void
ring_bluered::letter(char letter)
{
	for (int i = 0; i < LETTERCOUNT; i++) {
		if (this->letters[i].letter == letter) {
			Serial.println(letter);
			for (int l = 0; l < NUMRINGS; l++) {
				int r = this->letters[i].letterdots[l].ring;
				for (int led = 0; led < this->letters[i].letterdots[l].ledcount; led++) {
					int ringoffset = this->letters[i].letterdots[l].leds[led];
					CRGB c = leds[ring_led_to_offset(r, ringoffset)];
					c.r = 1;
					leds[ring_led_to_offset(r, ringoffset)] = c;
				}
			}
			return;
		}
	}
}

