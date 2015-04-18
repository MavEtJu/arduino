#include <Arduino.h>
#include "animation_fractals.h"

// ====================

/*
 * From http://en.wikipedia.org/wiki/Hilbert_curve
 *
 * A -> - B F + A F A + F B -
 * B -> + A F - B F B - F A + 
 */

MYCONSTRUCTOR_ANIMATION(LED_hilbert1)
{
    delayms = 25;
}

void
LED_hilbert1::animation(void)
{
    uint16_t dmax = step % (_VIEW_WIDTH * _VIEW_HEIGHT) + 10;

    for (uint16_t d = 0; d < dmax; d++) {
	int x, y;
	d2xy(_VIEW_WIDTH, d, &x, &y);
	_led->dot(x, y, _led->colour_transform(d));
    }
}

//convert (x,y) to d
int
LED_hilbert1::xy2d (int n, int x, int y)
{
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(s, &x, &y, rx, ry);
    }
    return d;
}
 
//convert d to (x,y)
void
LED_hilbert1::d2xy(int n, int d, int *x, int *y)
{
    int rx, ry, s, t=d;
    *x = *y = 0;
    for (s=1; s<n; s*=2) {
        rx = 1 & (t/2);
        ry = 1 & (t ^ rx);
        rot(s, x, y, rx, ry);
        *x += s * rx;
        *y += s * ry;
        t /= 4;
    }
}
 
//rotate/flip a quadrant appropriately
void
LED_hilbert1::rot(int n, int *x, int *y, int rx, int ry)
{
    if (ry == 0) {
        if (rx == 1) {
            *x = n-1 - *x;
            *y = n-1 - *y;
        }
 
        //Swap x and y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}

// ===========================

MYCONSTRUCTOR_ANIMATION(LED_tree1)
{
    delayms = 100;
    currangle_turn = 90;
    prevangle = 0;
    currangle = prevangle + currangle_turn;
    pathmax = _VIEW_WIDTH / 3;
    pathlength = pathmax;

    c_center.x = _VIEW_WIDTH / 2;
    c_center.y = _VIEW_HEIGHT / 2;
}

void
LED_tree1::prev(struct coordinates out,
		struct coordinates *in,
		int prevangle, int len)
{
    in->x = out.x - round(COS(prevangle) * len);
    in->y = out.y - round(SIN(prevangle) * len);
}

void
LED_tree1::next(struct coordinates in,
		struct coordinates *out1, struct coordinates *out2,
		int angle, int angleturn, int len)
{
    if (out1 != NULL) {
	out1->x = in.x + round(COS(angle + angleturn) * len);
	out1->y = in.y + round(SIN(angle + angleturn) * len);
    }
    if (out2 != NULL) {
	out2->x = in.x + round(COS(angle - angleturn) * len);
	out2->y = in.y + round(SIN(angle - angleturn) * len);
    }
}

void
LED_tree1::rotate(struct coordinates *c, int angle)
{
    struct coordinates c0;
    c0.x = c->x - c_center.x;
    c0.y = c->y - c_center.y;
    c->x = c_center.x + c0.x * COS(angle) - c0.y * SIN(angle);
    c->y = c_center.y + c0.x * SIN(angle) + c0.y * COS(angle);
}


void
LED_tree1::animation(void)
{
    struct coordinates c_start, c_target, c_end;
    struct coordinates c_P1;
    struct coordinates c_T1, c_T2, c_T11, c_T12, c_T21, c_T22;
    struct coordinates c_T111, c_T112, c_T121, c_T122;
    struct coordinates c_T211, c_T212, c_T221, c_T222;
    double m;

    m = 1 + 1.0 * (pathmax - pathlength) / pathmax;

    next(c_center, &c_target, NULL , currangle,   0, m * pathlength              );
    next(c_center, &c_start , NULL , currangle, 180, m * (pathmax - pathlength)    );
    next(c_center, &c_end   , NULL , currangle, 180, m * (2 * pathmax - pathlength));
    next(c_target, &c_T1    , &c_T2, currangle, currangle_turn, m * pathmax / 2  );
    prev(c_start,  &c_P1, prevangle, m * pathmax);

    next(c_T1 , &c_T11 , &c_T12 , currangle +     currangle_turn, currangle_turn, m * pathmax / 4);
    next(c_T2 , &c_T21 , &c_T22 , currangle +     currangle_turn, currangle_turn, m * pathmax / 4);
    next(c_T11, &c_T111, &c_T112, currangle + 2 * currangle_turn, currangle_turn, m * pathmax / 8);
    next(c_T12, &c_T121, &c_T122, currangle + 2 * currangle_turn, currangle_turn, m * pathmax / 8);
    next(c_T21, &c_T211, &c_T212, currangle + 2 * currangle_turn, currangle_turn, m * pathmax / 8);
    next(c_T22, &c_T221, &c_T222, currangle + 2 * currangle_turn, currangle_turn, m * pathmax / 8);

    // Line you came from
    _led->colour_set(_led->colour_fade(_led->colour_white, 0));
    _led->line(c_start, c_P1);

    // Current line you are on
    _led->colour_set(_led->colour_fade(_led->colour_white, 0));
    _led->line(c_end, c_target);

    // Next turn
    _led->colour_set(_led->colour_fade(_led->colour_white, 1));
    _led->line(c_T1, c_target);
    _led->line(c_T2, c_target);

    // Next next turn
    _led->colour_set(_led->colour_fade(_led->colour_white, 2));
    _led->line(c_T11, c_T1);
    _led->line(c_T12, c_T1);
    _led->line(c_T21, c_T2);
    _led->line(c_T22, c_T2);

    // Next next next turn
    _led->colour_set(_led->colour_fade(_led->colour_white, 3));
    _led->line(c_T111, c_T11);
    _led->line(c_T112, c_T11);
    _led->line(c_T121, c_T12);
    _led->line(c_T122, c_T12);
    _led->line(c_T211, c_T21);
    _led->line(c_T212, c_T21);
    _led->line(c_T221, c_T22);
    _led->line(c_T222, c_T22);

    //_led->dot(c_start, _led->colour_yellow);
    //_led->dot(c_center, _led->colour_red);
    //_led->dot(c_target, _led->colour_cyan);

    pathlength--;
    if (pathlength == 0) {
	pathlength = pathmax;
	prevangle = currangle;
	currangle += currangle_turn * (random() % 2 == 0 ? -1 : 1);

	//SERIAL4("prevangle:", prevangle, " currangle:", currangle);
    }
}

// ===========================
