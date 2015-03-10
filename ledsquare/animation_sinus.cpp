#include <Arduino.h>
#include "LED_Animation.h"
#include "animation_sinus.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

/* +----------------+
 * |   XXX   XX   XX|
 * |X  X  X X  X X  |
 * | XX   X X   XX  |
 * | XX   XX    X   |
 * | X     X    X   |
 * | XX   XX    XX  |
 * |X X   X X  X X  |
 * |X X  X  X  X X  |
 * |X  X X  X  X  X |
 * |   X X   XX   X |
 * |   XX    XX   X |
 * |    X    XX    X|
 * |    X    XX    X|
 * |   X X   XX   X |
 * |X  X X  X  X  X |
 * |XXX   XX   XXX  |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_sinus1)
{
    delayms = 50;
    c[0] = _led->colour_green;
    c[1] = _led->colour_yellow;
    c[2] = _led->colour_blue;
}

void
LED_sinus1::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;

    struct coordinates prev, now;

    for (int i = 0; i < 3; i++) {
	int first = 1;
	for (int16_t m = -1; m < _sVIEW_WIDTH; m++) {
	    int16_t o = m + step;
	    float f = (i * 120 + o * piece) * M_PI / 180;
	    float s = sin(f) * _VIEW_HEIGHT / 2 + _VIEW_HEIGHT / 2;

	    //SERIAL4("x,y: ", m, ",", (int)s);

	    now.x = m;
	    now.y = (int)s;
	    if (!first)
		_led->line(prev, now, c[i]);
	    prev = now;
	    first = 0;
	}
    }
}

// ==============================

/*
 * +----------------+
 * |                |
 * |                |
 * |            XXX |
 * |           X    |
 * |          X    X|
 * |                |
 * |         X      |
 * |X               |
 * | X      X       |
 * |                |
 * |  X    X        |
 * |      X         |
 * |   XXX          |
 * |                |
 * |                |
 * |                |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_sinus2)
{
    delayms = 25;
    height = VIEW_HEIGHT / 2;
    direction = -1;
}

void
LED_sinus2::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;
    if (step % 20 == 0) {
        height += direction;
        if (height == _sVIEW_HEIGHT / 5 || height == _sVIEW_HEIGHT / 2)
            direction *= -1;
    }

    for (uint16_t m = 0; m < _VIEW_WIDTH; m++) {
        uint16_t o = (m + step) % 7200;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * height;

        _led->dot(m, (int)s + _VIEW_HEIGHT / 2, _led->colour_yellow);
    }
}

// ===========================

/*
 * +----------------+
 * |                |
 * |                |
 * |                |
 * |X               |
 * | XX             |
 * |   XX           |
 * |     XX         |
 * |       X        |
 * |X       XX      |
 * | X        XX   X|
 * | X          X X |
 * |  X          XX |
 * |   X         X X|
 * |    X       X   |
 * |    XX     X    |
 * |      XXXXX     |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_sinus3)
{
    delayms = 15;
    c[0] = _led->colour_green;
    c[1] = _led->colour_yellow;
}

void
LED_sinus3::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;

    struct coordinates prev, now;

    for (int i = 1; i >= 0; i--) {
	int first = 1;
	for (int16_t m = -1; m < _sVIEW_WIDTH; m++) {
	    int16_t o = (m + step) % 7200;
	    float f = ((o * piece) * M_PI / 180 ) / (3 * i + 2);
	    float s = sin(f) * _VIEW_HEIGHT / 2 + _VIEW_HEIGHT / 2;

	    //SERIAL4("x,y: ", m, ",", (int)s);

	    now.x = m;
	    now.y = (int)s;
	    if (!first)
		_led->line(prev, now, c[i]);
	    prev = now;
	    first = 0;
	}
    }
}
