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
	    float f = i * 120 + o * piece;
	    float s = SIN(f) * _VIEW_HEIGHT / 2 + _VIEW_HEIGHT / 2;

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
        float f = piece * o;
        float s = SIN(f) * height;

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
    c[1] = _led->colour_blue;
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
	    float f = o * piece / (3.0 * i + 2.0);
	    float s = SIN(f) * _VIEW_HEIGHT / 2 + _VIEW_HEIGHT / 2;

	    now.x = m;
	    now.y = (int)s;
	    if (!first)
		_led->line(prev, now, c[i]);
	    prev = now;
	    first = 0;
	}
    }
}

// ======================================

/* +----------------+
 * |XXXxxxxxXXXXXXXX|
 * |xxxXXXxxxxXXXXXX|
 * |xxxxxxXXxxxxXXXX|
 * |XXXxxxxxXXxxxxXX|
 * |XXXXXXxxxxXXxxxX|
 * |XXXXXXXXxxxxXXxx|
 * |XXXXXXXXXXxxxxXx|
 * |XXXXXXXXXXXXxxxX|
 * |XXXXXXXXXXXXXXxx|
 * |XXXXXXXXXXXXXXXx|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_sinus4)
{
    delayms = 15;
    c_background = _led->colour_random_notblack();
    do {
	c_sinus = _led->colour_random_notblack();
    } while (_led->colour_same(c_sinus, c_background));
}

void
LED_sinus4::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;

    struct coordinates now;

    _led->square(0, 0, _VIEW_WIDTH, _VIEW_HEIGHT, c_background);

    for (int16_t m = 0; m < _sVIEW_WIDTH; m++) {
	int16_t o = (m + step) % 7200;
	float f = o * piece / 5.0;
	float s = SIN(f) * (_VIEW_HEIGHT / 2 - 2) + _VIEW_HEIGHT / 2;

	//SERIAL4("x,y: ", m, ",", (int)s);

	now.x = m;
	now.y = (int)s;
	_led->dot(now, c_sinus);

	_led->dot(now.x, now.y - 4, _led->colour_fade(c_background, 1));
	_led->dot(now.x, now.y - 3, _led->colour_fade(c_background, 1));
	_led->dot(now.x, now.y - 2, _led->colour_fade(c_background, 2));
	_led->dot(now.x, now.y - 1, _led->colour_fade(c_background, 2));
	_led->dot(now.x, now.y + 1, _led->colour_fade(c_background, 2));
	_led->dot(now.x, now.y + 2, _led->colour_fade(c_background, 2));
	_led->dot(now.x, now.y + 3, _led->colour_fade(c_background, 1));
	_led->dot(now.x, now.y + 4, _led->colour_fade(c_background, 1));
    }
}

// ======================================

/*
 * +----------------+
 * |xxxxxxxxxxxxxxxx|
 * |xxxxxxxxxxxxxxxx|
 * |xxxxxxxxxxxxxxxx|
 * |xxxxxxxxxxxxxxxx|
 * |xxxxxxxxxxxxxxxx|
 * |.xxxxxxxxxxxxxxx|
 * |X..xxxxxxxxxxxxx|
 * |XXX.xxxxxxxxxxxx|
 * |XXXX..xxxxxxxxxx|
 * |XXXXXX..xxxxxxxx|
 * |XXXXXXXX.xxxxxxx|
 * |XXXXXXXXX..xxxxx|
 * |XXXXXXXXXXX..xxx|
 * |XXXXXXXXXXXXX..x|
 * |XXXXXXXXXXXXXXX.|
 * |XXXXXXXXXXXXXXXX|
 * +----------------+
 */


MYCONSTRUCTOR_ANIMATION(LED_sinus5)
{
    delayms = 15;
    c_sinus = _led->colour_random_notblack();
    do {
	c_background1 = _led->colour_random_notblack();
    } while (_led->colour_same(c_sinus, c_background1));
    do {
	c_background2 = _led->colour_random_notblack();
    } while (_led->colour_same(c_background2, c_background1) &&
	     _led->colour_same(c_sinus, c_background1));
}

void
LED_sinus5::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;
    struct coordinates now;

    for (int16_t m = 0; m < _sVIEW_WIDTH; m++) {
	int16_t o = (m + step) % 7200;
	float f = o * piece / 5.0;
	float s = SIN(f) * (_VIEW_HEIGHT / 2 - 1) + _VIEW_HEIGHT / 2;

	now.x = m;
	now.y = (int)s;

	_led->verline(now.x, 0, now.y, c_background1);
	_led->verline(now.x, now.y, _VIEW_HEIGHT, c_background2);
	_led->dot(now, c_sinus);
    }
}

// =====================================

/*
 * +----------------+
 * |                |
 * |                |
 * |XX              |
 * | X              |
 * | X              |
 * |  X             |
 * |  X             |
 * |  XX            |
 * |   X            |
 * |   X            |
 * |    X           |
 * |     X          |
 * |     X        X |
 * |      X      X  |
 * |       X    XX  |
 * |        XXXXX   |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_lissajou1)
{
    delayms = 1;
}

void
LED_lissajou1::animation(void)
{
    if (step % 1000 == 0) {
	numpoints = 1 + random() % 5;
	a = 1 + random() % 5;
	b = 1 + random() % 5;
	colour = _led->colour_random_notblack();
    }

    struct coordinates c;

    c.x = (int16_t)(_VIEW_WIDTH / 2 + _VIEW_WIDTH * SIN(a * step) / 2);
    c.y = (int16_t)(_VIEW_HEIGHT / 2 + _VIEW_HEIGHT * SIN(b * step) / 2);
    shift_history(c);

    for (int i = 0; i < LED_lissajou1_history; i++) {
	_led->dot(history[i], colour);
    }
}

void
LED_lissajou1::shift_history(struct coordinates c)
{
    for (int i = LED_lissajou1_history - 1; i > 0; i--) {
	history[i] = history [i - 1];
    }
    history[0] = c;
}

// =====================================

/*
 * +----------------+
 * |         XX     |
 * |         XX     |
 * |        X X     |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |        X       |
 * |         X      |
 * |         X      |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_rose1)
{
    delayms = 1;
}

void
LED_rose1::animation(void)
{
    if (step % 1000 == 0) {
	numpoints = 1 + random() % 5;
	a = 1 + random() % 5;
	colour = _led->colour_random_notblack();
    }

    struct coordinates c;

    c.x = (int16_t)(_VIEW_WIDTH / 2  + _VIEW_WIDTH  * COS(a * step) * COS(step) / 2);
    c.y = (int16_t)(_VIEW_HEIGHT / 2 + _VIEW_HEIGHT * COS(a * step) * SIN(step) / 2);
    shift_history(c);
 
    for (int i = 0; i < LED_rose1_history; i++) {
	_led->dot(history[i], colour);
    }
}

void
LED_rose1::shift_history(struct coordinates c)
{
    for (int i = LED_rose1_history - 1; i > 0; i--) {
	history[i] = history [i - 1];
    }
    history[0] = c;
}
