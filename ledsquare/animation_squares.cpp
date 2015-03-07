#include <Arduino.h>
#include "LED_Animation.h"
#include "A_Tools.h"
#include "animation_squares.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ============================

LED_squares1::LED_squares1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT) {
    c = _led->colour_random();
}

void
LED_squares1::animation(void)
{
    uint16_t m = step % (2 * _VIEW_HEIGHT);

    if (m == 0)
	c = _led->colour_random_notblack();
    _led->colour_set(c);

    if (m < _VIEW_HEIGHT) {
        _led->line(0, 0, 0, m);
        _led->line(0, m, m, m);
        _led->line(m, m, m, 0);
        _led->line(m, 0, 0, 0);
    } else {
        m %= _VIEW_HEIGHT;
        _led->line(_VIEW_HEIGHT - 1, _VIEW_HEIGHT - 1, _VIEW_HEIGHT - 1, m);
        _led->line(_VIEW_HEIGHT - 1, m, m, m);
        _led->line(m, m, m, _VIEW_HEIGHT - 1);
        _led->line(m, _VIEW_HEIGHT - 1, _VIEW_HEIGHT - 1, _VIEW_HEIGHT - 1);
    }
}

// ============================

LED_squares2::LED_squares2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT) {
    for (int i = LED_squares2_history - 1; i >= 0; i--) {
	a[i].c1.x = 0;
	a[i].c1.y = 0;
	a[i].c2.x = 0;
	a[i].c2.y = 0;
        c[i] = _led->colour_black;
    }
    delayms = 250;
}

void
LED_squares2::animation(void)
{
    struct area a_new;
    LED c_new;
    int i;
    int16_t x1, x2, y1, y2;

    do {
        c_new = _led->colour_random_notblack();
    } while (c_new.red == c_last.red && c_new.green == c_last.green && c_new.blue == c_last.blue);
    x1 = random() % _VIEW_WIDTH;
    x2 = random() % _VIEW_WIDTH;
    y1 = random() % _VIEW_HEIGHT;
    y2 = random() % _VIEW_HEIGHT;
    if (x1 > x2) {
        int16_t x = x1;
        x1 = x2;
        x2 = x;
    }
    if (y1 > y2) {
        int16_t y = y1;
        y1 = y2;
        y2 = y;
    }
    a_new.c1.x = x1;
    a_new.c1.y = y1;
    a_new.c2.x = x2;
    a_new.c2.y = y2;

    shift_history(a_new, c_new);
    c_last = c_new;

    for (i = LED_squares2_history - 1; i >= 0; i--) {
	_led->square(a[i], _led->colour_fade(c[i], i / 5));
    }
}

void
LED_squares2::shift_history(struct area a_new, LED c_new)
{
    for (int i = LED_squares2_history - 1; i > 0; i--) {
	a[i] = a[i - 1];
	c[i] = c[i - 1];
    }
    a[0] = a_new;
    c[0] = c_new;
}

// ============================

LED_movingsquares1::LED_movingsquares1(LED_Strip *l, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(l, VIEW_WIDTH, VIEW_HEIGHT)
{
    delayms = 50;
    
    c[0] = _led->colour_magenta; //_led->colour_random();
    c[3] = _led->colour_red; //_led->colour_random();
    c[2] = _led->colour_green;
    c[1] = _led->colour_yellow;

    size[0] = 5;
    size[3] = 3;
    size[2] = 2;
    size[1] = 4;
    x0[0] = 0;
    y0[0] = 0;
    x0[3] = 4;
    y0[3] = 4;
    x0[2] = 1;
    y0[2] = 1;
    x0[1] = 3;
    y0[1] = 3;
    
    for (int i = 0; i < LED_movingsquares1_squares; i++) {
	x1[i] = _VIEW_WIDTH - size[i] - y0[i];
	y1[i] = _VIEW_HEIGHT - size[i] - x0[i];
	x[i] = x0[i];
	y[i] = y0[i];
    }
}

void
LED_movingsquares1::animation(void)
{
    /*
     * ................
     * ................
     * ................
     * ................
     * ................
     * ................
     * ................
     * ................
     * ....****........
     * ....****........
     * .XXX****........
     * .XXX****........
     * .XXXXX..........
     * .XXXXX..........
     * .XXXXX..........
     * ................
     *
     *
     */

    for (int i = 0; i < LED_movingsquares1_squares; i++) {
	if (x[i] == x0[i] && y[i] == y0[i]) {
	    dx[i] = i % 2 == 0 ? 1 : 0;
	    dy[i] = i % 2 == 0 ? 0 : 1;
	}
	if (x[i] == x1[i] && y[i] == y0[i]) {
	    dx[i] = i % 2 == 0 ? 0 : -1;
	    dy[i] = i % 2 == 0 ? 1 : 0;
	}
	if (x[i] == x0[i] && y[i] == y1[i]) {
	    dx[i] = i % 2 == 0 ? 0 : 1;
	    dy[i] = i % 2 == 0 ? -1 : 0;
	}
	if (x[i] == x1[i] && y[i] == y1[i]) {
	    dx[i] = i % 2 == 0 ? -1 : 0;
	    dy[i] = i % 2 == 0 ? 0 : -1;
	}

	/*
	Serial.print("dx,dy: ");
	Serial.print(dx[i]);
	Serial.print(",");
	Serial.print(dy[i]);
	Serial.println("");
	*/

	x[i] += dx[i];
	y[i] += dy[i];

	_led->square(x[i], y[i], size[i], size[i], c[i]);
    }
}
