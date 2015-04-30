#include <Arduino.h>
#include "LED_Animation.h"
#include "A_Tools.h"
#include "animation_lines.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

/*
 * +----------------+
 * |.XX             |
 * |..XX            |
 * | ..X            |
 * |  ..X           |
 * |   .XX          |
 * |     XX         |
 * |      X         |
 * |       X        |
 * |        X       |
 * |         X      |
 * |         XX     |
 * |          XX.   |
 * |           X..  |
 * |            X.. |
 * |            XX..|
 * |             XX.|
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_cross1)
{
    memset(c1, 0, sizeof(struct coordinates) * LED_cross1_history);
    memset(c2, 0, sizeof(struct coordinates) * LED_cross1_history);
    c[0] = _led->Color(16, 0, 0);
    c[1] = _led->Color(8, 0, 0);
    c[2] = _led->Color(4, 0, 0);
    c[3] = _led->Color(2, 0, 0);
    c[4] = _led->Color(1, 0, 0);
}

void
LED_cross1::animation(void)
{
    uint16_t x1, y1, x2, y2;
    uint8_t around = (_VIEW_HEIGHT + _VIEW_WIDTH - 2);
    
    if (step % around < _VIEW_HEIGHT) {
        x1 = 0;
        y1 = step % around;
        x2 = _VIEW_WIDTH - 1;
        y2 = _VIEW_HEIGHT - y1 - 1;
    } else {
        x1 = step % around - _VIEW_HEIGHT + 1;
        y1 = _VIEW_HEIGHT - 1;
        x2 = _VIEW_WIDTH - x1 - 1;
        y2 = 0;
    }
    
    for (int i = LED_cross1_history - 1; i > 0; i--) {
        c1[i] = c1[i - 1];
        c2[i] = c2[i - 1];
    }
    c1[0].x = x1;
    c1[0].y = y1;
    c2[0].x = x2;
    c2[0].y = y2;
    for (int i = LED_cross1_history - 1; i >= 0; i--) {
        if ((int16_t)delayms / 20 > LED_cross1_history - i - 1) {
            continue;
        }
        _led->line(c1[i], c2[i], _led->colour_fade(_led->colour_transform(step), i / 2));
    }
    
    delayms = 50 + (int16_t)(45 * SIN(step));
}

// ==============================

void
LED_lineshorver1::animation(void)
{
    uint16_t m = step % (2 * _VIEW_HEIGHT);

    _led->colour_set(_led->colour_magenta);
    if (m < _VIEW_HEIGHT)
        _led->line(0, m, _VIEW_WIDTH, m);
    else
        _led->line(m % _VIEW_HEIGHT, 0, m % _VIEW_HEIGHT, _VIEW_WIDTH);
}

// ============================

/*
 * +----------------+
 * |                |
 * |                |
 * |X               |
 * |XX              |
 * |xXX             |
 * |.xXXX           |
 * |...xXX          |
 * | ...xXX         |
 * |   ..xXX        |
 * |     ..XX       |
 * |      ..xX      |
 * |        .xX     |
 * |          .XX   |
 * |           .XX  |
 * |             xX |
 * |               X|
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_lines1)
{
    x1 = y1 = 0;
    x2 = _VIEW_WIDTH - 1;
    y2 = _VIEW_HEIGHT - 1;
    x1_final = x1;
    x2_final = x2;
    y1_final = y1;
    y2_final = y2;

    for (uint8_t i = 0; i < 3; i++) {
        x1s[i] = x1;
        y1s[i] = y1;
        x2s[i] = x2;
        y2s[i] = y2;
    }
    dir = 0;
    c[0] = _led->Color(16, 0, 0);
    c[1] = _led->Color(8, 0, 0);
    c[2] = _led->Color(4, 0, 0);
    c[3] = _led->Color(2, 0, 0);
    c[4] = _led->Color(1, 0, 0);
    delayms = 40;
}

void
LED_lines1::shift_history(void)
{
    for (uint8_t i = LED_lines1_history - 1; i > 0; i--) {
        x1s[i] = x1s[i - 1];
        y1s[i] = y1s[i - 1];
        x2s[i] = x2s[i - 1];
        y2s[i] = y2s[i - 1];
    }
    x1s[0] = x1;
    y1s[0] = y1;
    x2s[0] = x2;
    y2s[0] = y2;
}

void
LED_lines1::animation(void)
{
    /* There are several different modes:
     *
     * 0: x1, y1 move, x2, y2 still
     * 1: x1, y1 still, x2, y2 move
     * 2: x1, x2 move, y1, y2 still
     * 3: x1, x2 still, y1, y2 move
     * 4: x1 move, y1, x2, y2 still
     * 5: y1 move, x1, x2, y2 still
     * 6: x2 move, x1, y1, y2 still
     * 7: y2 move, x1, y1, x2 still

     */

    if (x1 == x1_final && x2 == x2_final && y1 == y1_final && y2 == y2_final) {
        dir = random() % 8;
        switch (dir) {
            case 0:
                dx1 = x1 == 0 ? 1 : -1;
                dy1 = y1 == 0 ? 1 : -1;
                dx2 = dy2 = 0;
                x1_final = dx1 == 1 ? _VIEW_WIDTH - 1 : 0;
                y1_final = dy1 == 1 ? _VIEW_HEIGHT - 1 : 0;
                x2_final = x2;
                y2_final = y2;
                break;
            case 1:
                dx1 = dy1 = 0;
                dx2 = x2 == 0 ? 1 : -1;
                dy2 = y2 == 0 ? 1 : -1;
                x1_final = x1;
                y1_final = y1;
                x2_final = dx2 == 1 ? _VIEW_WIDTH - 1 : 0;
                y2_final = dy2 == 1 ? _VIEW_HEIGHT - 1 : 0;
                break;
            case 2:
                dx1 = x1 == 0 ? 1 : -1;
                dx2 = x2 == 0 ? 1 : -1;
                dy1 = dy2 = 0;
                x1_final = dx1 == 1 ? _VIEW_WIDTH - 1 : 0;
                x2_final = dx2 == 1 ? _VIEW_WIDTH - 1 : 0;
                y1_final = y1;
                y2_final = y2;
                break;
            case 3:
                dx1 = dx2 = 0;
                dy1 = y1 == 0 ? 1 : -1;
                dy2 = y2 == 0 ? 1 : -1;
                x1_final = x1;
                x2_final = x2;
                y1_final = dy1 == 1 ? _VIEW_HEIGHT - 1 : 0;
                y2_final = dy2 == 1 ? _VIEW_HEIGHT - 1 : 0;
                break;
            case 4:
                dx1 = x1 == 0 ? 1 : -1;
                dy1 = dx2 = dy2 = 0;
                x1_final = dx1 == 1 ? _VIEW_WIDTH - 1 : 0;
                y1_final = y1;
                x2_final = x2;
                y2_final = y2;
                break;
            case 5:
                dy1 = y1 == 0 ? 1 : -1;
                dx1 = dx2 = dy2 = 0;
                x1_final = x1;
                y1_final = dy1 == 1 ? _VIEW_HEIGHT - 1 : 0;
                x2_final = x2;
                y2_final = y2;
                break;
            case 6:
                dx2 = x2 == 0 ? 1 : -1;
                dx1 = dy1 = dy2 = 0;
                x1_final = x1;
                y1_final = y1;
                x2_final = dx2 == 1 ? _VIEW_WIDTH - 1 : 0;
                y2_final = y2;
                break;
            case 7:
                dy2 = y2 == 0 ? 1 : -1;
                dx1 = dy1 = dx2 = 0;
                x1_final = x1;
                y1_final = y1;
                x2_final = x2;
                y2_final = dy2 == 1 ? _VIEW_HEIGHT - 1 : 0;
                break;
        }
    }

    x1 += dx1;
    y1 += dy1;
    x2 += dx2;
    y2 += dy2;
    shift_history();
    for (int8_t i = LED_lines1_history - 1; i >= 0; i--) {
        _led->line(x1s[i], y1s[i], x2s[i], y2s[i], c[i]);
    }
}

// ==================

/*
 * +----------------+
 * |          X     |
 * |          .X    |
 * |     X     .X   |
 * |   XX..    .X   |
 * |  X....     .X  |
 * | X..        .   |
 * |                |
 * |                |
 * |                |
 * |                |
 * |   .         ..X|
 * |  X.      ....X |
 * |   X.     ..XX  |
 * |   X.      X    |
 * |    X.          |
 * |     X          |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_lines2)
{
    x0 = 0;
    y0 = 0;
    length = 5;
    angle = 0;
    delayms = 25;
    colour = _led->colour_random_notblack();
    memset(history, '\0', sizeof(history[0]) * LED_lines2_history);

    coor = 0;

    c = (struct LED_lines2_coordinates *)malloc(sizeof(struct LED_lines2_coordinates) * 2 * (_VIEW_WIDTH / length + _VIEW_HEIGHT / length));

    int ic = 0;
    for (int y = 0; y < _sVIEW_HEIGHT - 1; y += length) {
	c[ic].c.x = 0;
	c[ic].c.y = y;
	c[ic].a0 = y == 0 ? 0 : 270;
	c[ic].a1 = y == _sVIEW_HEIGHT - 1 ? 0 : 90;
	ic++;
    }
    for (int x = 0; x < _sVIEW_WIDTH - 1; x += length) {
	c[ic].c.x = x;
	c[ic].c.y = _VIEW_HEIGHT - 1;
	c[ic].a0 = x == 0 ? 270 : 180;
	c[ic].a1 = x == _sVIEW_WIDTH - 1 ? 270 : 0;
	ic++;
    }
    for (int y = _sVIEW_HEIGHT - 1; y > 0; y -= length) {
	c[ic].c.x = _VIEW_WIDTH - 1;
	c[ic].c.y = y;
	c[ic].a0 = y == _sVIEW_HEIGHT - 1 ? 180 : 90;
	c[ic].a1 = y == 0 ? 180 : 270;
	ic++;
    }
    for (int x = _sVIEW_WIDTH - 1; x > 0; x -= length) {
	c[ic].c.x = x;
	c[ic].c.y = 0;
	c[ic].a0 = x == _sVIEW_WIDTH - 1 ? 90 : 0;
	c[ic].a1 = x == 0 ? 90 : 180;
	ic++;
    }

    ics = ic;
}

void
LED_lines2::shift_history(int16_t c1x, int16_t c1y, int16_t c2x, int16_t c2y)
{
    for (int i = LED_lines2_history - 1; i > 0; i--) {
	history[i] = history[i - 1];
    }
    history[0].c1.x = c1x;
    history[0].c1.y = c1y;
    history[0].c2.x = c2x;
    history[0].c2.y = c2y;
}

void
LED_lines2::animation(void)
{

    double si = SIN(angle);
    double co = COS(angle);

    shift_history(c[coor].c.x, c[coor].c.y,
	(int16_t)(c[coor].c.x + co * length),
	(int16_t)(c[coor].c.y + si * length));

    for (int i = LED_lines2_history - 1; i >= 0; i--) {
	_led->line(
	    history[i].c1.x, history[i].c1.y,
	    history[i].c2.x, history[i].c2.y,
	    _led->colour_fade(_led->colour_transform(step), i));

	_led->line(
	    _VIEW_WIDTH - 1 - history[i].c1.x, _VIEW_HEIGHT - 1 - history[i].c1.y,
	    _VIEW_WIDTH - 1 - history[i].c2.x, _VIEW_HEIGHT - 1 - history[i].c2.y,
	    _led->colour_fade(_led->colour_transform(step), i));

	_led->line(
	    _VIEW_WIDTH - history[i].c1.y, history[i].c1.x,
	    _VIEW_WIDTH - history[i].c2.y, history[i].c2.x,
	    _led->colour_fade(_led->colour_transform(step + ics), i));

	_led->line(
	    history[i].c1.y, _VIEW_HEIGHT - 1 - history[i].c1.x,
	    history[i].c2.y, _VIEW_HEIGHT - 1 - history[i].c2.x,
	    _led->colour_fade(_led->colour_transform(step + ics), i));

    }

    angle += 10;
    angle %= 360;

    if (c[coor].a1 == angle) {
	coor++;
	coor %= ics;
	angle = c[coor].a0;
	SERIAL9(coor, ": ", c[coor].c.x, ",", c[coor].c.y, " ", c[coor].a0, " ", c[coor].a1);
    }
    //SERIAL2("angle: ", angle);
}

// =============================

/*
 * +----------------+
 * |       XXXXXXXXX|
 * |       XXXXXXXXX|
 * |XXXXXXXXX       |
 * |XXXXXXXXX       |
 * |       XXXXXXXXX|
 * |       XXXXXXXXX|
 * |XXXXXXXXX       |
 * |XXXXXXXXX       |
 * |       XXXXXXXXX|
 * |       XXXXXXXXX|
 * |XXXXXXXXX       |
 * |XXXXXXXXX       |
 * |       XXXXXXXXX|
 * |       XXXXXXXXX|
 * |XXXXXXXXX       |
 * |XXXXXXXXX       |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_lines3)
{
    delayms = 35;
}

void
LED_lines3::animation(void)
{
    int x = 1 + step % _VIEW_WIDTH;
    if (x == 1) {
	c[0] = _led->colour_random_notblack();
	do {
	    c[1] = _led->colour_random_notblack();
	} while (_led->colour_same(c[0], c[1]));

	stripes = 1 << (step / _VIEW_HEIGHT) % 4;
    }


    for (int i = 0; i < stripes; i++) {
	_led->square(0, i * (_VIEW_HEIGHT / stripes),
		     x, (_VIEW_HEIGHT / stripes) / 2, c[0]);
	_led->square(_VIEW_WIDTH - x, i * (_VIEW_HEIGHT / stripes) + (_VIEW_HEIGHT / stripes / 2),
		     x, (_VIEW_HEIGHT / stripes) / 2, c[1]);
    }
}

// =========================

/*
 * +----------------+
 * |x    x    xx   x|
 * |x     x         |
 * |x      xx       |
 * | x       x      |
 * | x          xxx |
 * |xx   x    xx   x|
 * |x     x         |
 * |x      xx       |
 * | x       x      |
 * | x          xxx |
 * |xx   x    xx   x|
 * |x     x         |
 * |x      xx       |
 * | x       x      |
 * | x          xxx |
 * |xx   x    xx   x|
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_lines_waver1)
{
    delayms = 25l;
    number = 4;
    len = _VIEW_WIDTH / (number - 1);
    angle = 0;
}

void
LED_lines_waver1::animation(void)
{
    for (int16_t i = 0; i < number * number; i++) {
	int x = i % number;
	int y = i / number;
	_led->line(x * len, y * len, 
	    x * len + len * COS(x * 45 + angle),
	    y * len + len * SIN(x * 45 + angle),
	    _led->colour_transform(step + i)
	);
    }

    angle += 10;
    angle %= 360;
}

// =================================

/*
 * +----------------+
 * |     .          |
 * |     X    .     |
 * |     X    X     |
 * |          X     |
 * |                |
 * |                |
 * |                |
 * |      .         |
 * |      x      .x |
 * |      x         |
 * |             . .|
 * |             x X|
 * |             x X|
 * |    X          X|
 * |    X      .   X|
 * |    .     XX    |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_lines_worm1)
{
    for (int w = 0; w < LED_lines_worm1s; w++) {
	for (int i = 0; i < LED_lines_worm1_history; i++) {
	    history[w][i].x = _VIEW_WIDTH / 2;
	    history[w][i].y = _VIEW_HEIGHT / 2;
	}
	dx[w] = 1;
	dy[w] = 0;
	c[w] = _led->colour_random_notblack();
    }
}

void
LED_lines_worm1::animation(void)
{
    for (int w = 0; w < LED_lines_worm1s; w++) {
	for (int i = LED_lines_worm1_history - 1; i > 0; i--) {
	    history[w][i] = history[w][i - 1];
	    _led->dot(history[w][i],
	    _led->colour_fade(c[w], i));
	}
	int x = history[w][0].x;
	int y = history[w][0].y;
	_led->dot(history[w][0], c[w]);

	if ((dx[w] == 1  && x == _sVIEW_WIDTH - 1)
	 || (dx[w] == -1 && x == 0)
	 || (dy[w] == 1  && y == _sVIEW_HEIGHT - 1)
	 || (dy[w] == -1 && y == 0)
	 || (random() % (_VIEW_WIDTH / 2) == 0)) {
	    int _dx = dx[w];
	    int _dy = dy[w];
	    do {
		dy[w] = _dx * (random() % 2 == 0 ? -1 : 1);
		dx[w] = _dy * (random() % 2 == 0 ? -1 : 1);
	    } while ((dx[w] == 1  && x == _sVIEW_WIDTH - 1)
		  || (dx[w] == -1 && x == 0)
		  || (dy[w] == 1  && y == _sVIEW_HEIGHT - 1)
		  || (dy[w] == -1 && y == 0));
	}

	x += dx[w];
	y += dy[w];

	history[w][0].x = x;
	history[w][0].y = y;
	_led->dot(history[w][0], c[w]);
    }
}

