#include <Arduino.h>
#include "LED_Animation.h"
#include "animation_torches.h"
#include "A_Tools.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

MYCONSTRUCTOR_ANIMATION(LED_torch1)
{
    colour_floor = _led->Color(9 << 2, 4, 0);

    numcoals = 32;
    coals = (struct coal *)malloc(numcoals * sizeof(coals));
    if (coals == NULL) {
	SERIAL3(F("coals=NULL in LED_torch1 for "), numcoals * sizeof(coals), F("BYTES"));
#ifdef DEBUG_MEMORY
	FREERAM("LED_torch1");
	FREEMEMORY("LED_torch1");
#endif
	broken = 1;
	return;
    }

    for (uint8_t c = 0; c < numcoals; c++) {
        coals[c].x = 0;
        coals[c].y = 1;
    }
}

LED_torch1::~LED_torch1(void)
{
    free(coals);
}

void
LED_torch1::animation(void)
{
    for (uint8_t c = 0; c < numcoals; c++) {
	// There is a 50% chance that a light goes higher
	if (random() % 100 > 66) {
	    // Back to the beginning
	    coals[c].x = random() % _VIEW_WIDTH;
	    coals[c].y = 1;
	} else {
	    coals[c].y++;
	}
	_led->dot(coals[c].x % _VIEW_WIDTH, coals[c].y,
	    _led->Color((_VIEW_HEIGHT - coals[c].y) << 2, _VIEW_HEIGHT - coals[c].y > 1, 0));
    }
    _led->line(0, 0, _VIEW_WIDTH, 0, colour_floor);
}

// ===============

MYCONSTRUCTOR_ANIMATION(LED_torch2)
{    
#ifdef DEBUG_MEMORY
    FREERAM("LED_torch2: init");
    FREEMEMORY("LED_torch2: init");
#endif
    numcoals = 30;
    coals = (struct coal *)malloc(numcoals * sizeof(struct coal));
    if (coals == NULL) {
	SERIAL3(F("coals=NULL in LED_torch2 for "), numcoals * sizeof(coals), F(" bytes"));
#ifdef DEBUG_MEMORY
	FREERAM("LED_torch2");
	FREEMEMORY("LED_torch2");
#endif
	broken = 1;
	return;
    }
    
    for (int c = 0; c < numcoals; c++) {
        coals[c] = new_coal(_VIEW_HEIGHT, 1);
    }
}

struct coal
LED_torch2::new_coal(uint8_t intensity, int randomy)
{
    struct coal c;
    c.x = random() % _VIEW_WIDTH;
    c.y = randomy ? random() % _VIEW_HEIGHT : 0;
    c.intensity = intensity + 2 - (random() % 5);;
    c.decay = random() % 4 + 2;
    return c;
}

LED_torch2::~LED_torch2(void)
{
    free(coals);
}

void
LED_torch2::animation(void)
{
    // Change in intensity of the lowest level
    uint32_t piece = 360 / (4 * _VIEW_WIDTH);
    uint16_t o = step;
    float f = piece * M_PI / 180 * o;
    float s = sin(f) * _VIEW_HEIGHT;
    uint8_t floor_intensity = (_VIEW_HEIGHT << 1) + (int)s;
    LED colour_floor = _led->Color(floor_intensity, floor_intensity, 0);
       
    for (int c = 0; c < numcoals; c++) {
        coals[c].y++;
        coals[c].intensity -= coals[c].decay;
        if (coals[c].y == _sVIEW_HEIGHT || coals[c].intensity <= 0) {
            coals[c] = new_coal(floor_intensity, 0);
        }

        int16_t x = coals[c].x;
        int16_t y = coals[c].y;

        /* Spark around the flame */
        if (coals[c].intensity > 2) {
            LED colour_spark = _led->Color(2, 2, 0);
            colour_spark = _led->Color(2, 2, 0);
            if (y > 0) {
                _led->dot(x - 1, y, colour_spark);
                _led->dot(x + 1, y, colour_spark);
            }
            if (y > 1)
                _led->dot(x, y - 1, colour_spark);
            _led->dot(x, y + 1, colour_spark);
        }
    }

    for (int c = 0; c < numcoals; c++) {
        _led->dot(coals[c].x % _VIEW_WIDTH, coals[c].y,
            _led->Color(coals[c].intensity, coals[c].intensity, 0));
    }

    _led->line(0, 0, _VIEW_WIDTH, 0, colour_floor);
}
