#include <Arduino.h>
#include "LED_Animation.h"
#include "A_Tools.h"
#include "animation_lines.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

LED_cross1::LED_cross1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
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
        _led->line(c1[i], c2[i], c[i]);
    }
    
    delayms = 50 + 45 * sin(step / 180.0 * M_PI);
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

LED_lines1::LED_lines1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
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

LED_lines2::LED_lines2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    x0 = 0;
    y0 = 0;
    length = 5;
    angle = 0;
    delayms = 25;
    colour = _led->colour_random_notblack();

    coor = 0;

    // Bottom left
    c[0].c.x = 0;
    c[0].c.y = 0;
    c[0].a0 = 0;
    c[0].a1 = 90;

    c[1].c.x = 0;
    c[1].c.y = 5;
    c[1].a0 = 270;
    c[1].a1 = 90;

    c[2].c.x = 0;
    c[2].c.y = 10;
    c[2].a0 = 270;
    c[2].a1 = 90;

    c[3].c.x = 0;
    c[3].c.y = 15;
    c[3].a0 = 270;
    c[3].a1 = 0;

    c[4].c.x = 5;
    c[4].c.y = 15;
    c[4].a0 = 180;
    c[4].a1 = 0;

    c[5].c.x = 10;
    c[5].c.y = 15;
    c[5].a0 = 180;
    c[5].a1 = 0;

    c[6].c.x = 15;
    c[6].c.y = 15;
    c[6].a0 = 180;
    c[6].a1 = 270;

    c[7].c.x = 15;
    c[7].c.y = 10;
    c[7].a0 = 90;
    c[7].a1 = 270;

    c[8].c.x = 15;
    c[8].c.y = 5;
    c[8].a0 = 90;
    c[8].a1 = 270;

    c[9].c.x = 15;
    c[9].c.y = 0;
    c[9].a0 = 90;
    c[9].a1 = 180;

    c[10].c.x = 10;
    c[10].c.y = 0;
    c[10].a0 = 0;
    c[10].a1 = 180;

    c[11].c.x = 5;
    c[11].c.y = 0;
    c[11].a0 = 0;
    c[11].a1 = 180;

    memset(history, '\0', sizeof(history[0]) * LED_lines2_history);
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

    double si = sin(M_PI * angle / 180);
    double co = cos(M_PI * angle / 180);

    shift_history(c[coor].c.x, c[coor].c.y,
	c[coor].c.x + co * length, c[coor].c.y + si * length);

    for (int i = LED_lines2_history - 1; i >= 0; i--) {
	_led->line(
	    history[i].c1.x, history[i].c1.y,
	    history[i].c2.x, history[i].c2.y,
	    _led->colour_fade(colour, i));

	_led->line(
	    _VIEW_WIDTH - 1 - history[i].c1.x, _VIEW_HEIGHT - 1 - history[i].c1.y,
	    _VIEW_WIDTH - 1 - history[i].c2.x, _VIEW_HEIGHT - 1 - history[i].c2.y,
	    _led->colour_fade(colour, i));

	_led->line(
	    _VIEW_WIDTH - history[i].c1.y, history[i].c1.x,
	    _VIEW_WIDTH - history[i].c2.y, history[i].c2.x,
	    _led->colour_fade(colour, i));

	_led->line(
	    history[i].c1.y, _VIEW_HEIGHT - 1 - history[i].c1.x,
	    history[i].c2.y, _VIEW_HEIGHT - 1 - history[i].c2.x,
	    _led->colour_fade(colour, i));

    }

    angle += 10;
    angle %= 360;

    if (c[coor].a1 == angle) {
	coor++;
	coor %= 12;
	angle = c[coor].a0;
    }
}
