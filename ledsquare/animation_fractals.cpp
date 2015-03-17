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
    delayms = 200;
    angleturn = angle = nextangle_current = nextangle_target = angleturn = 90;
    nextangle_turn = 30;
    pathmax = _VIEW_WIDTH / 2;
    pathlength = pathmax;

    c_center.x = _VIEW_WIDTH / 2;
    c_center.y = _VIEW_HEIGHT / 2;
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
    struct coordinates c_start, c_target;
    struct coordinates c_T1, c_T2, c_T11, c_T12, c_T21, c_T22;
    struct coordinates c_T111, c_T112, c_T121, c_T122;
    struct coordinates c_T211, c_T212, c_T221, c_T222;

    next(c_center, &c_target, NULL , angle, 0  , 2 * pathlength              );
    next(c_center, &c_start , NULL , angle, 180, 2 * pathmax - 2 * pathlength);
    next(c_target, &c_T1    , &c_T2, angle, angleturn, pathmax / 2);

    next(c_T1 , &c_T11 , &c_T12 , angle +     angleturn, angleturn, pathmax / 4);
    next(c_T2 , &c_T21 , &c_T22 , angle +     angleturn, angleturn, pathmax / 4);
    next(c_T11, &c_T111, &c_T112, angle + 2 * angleturn, angleturn, pathmax / 8);
    next(c_T12, &c_T121, &c_T122, angle + 2 * angleturn, angleturn, pathmax / 8);
    next(c_T21, &c_T211, &c_T212, angle + 2 * angleturn, angleturn, pathmax / 8);
    next(c_T22, &c_T221, &c_T222, angle + 2 * angleturn, angleturn, pathmax / 8);

    if (nextangle_target != nextangle_current) {
	nextangle_current += (nextangle_target > nextangle_current ? 1 : -1) * nextangle_turn;
	SERIAL2("Angle: ", angle);
	SERIAL4("nextangle_current:", nextangle_current, " nextangle_target:", nextangle_target);
	rotate(&c_start, nextangle_current - angle);
	rotate(&c_target, nextangle_current - angle);
	rotate(&c_T1, nextangle_current - angle);
	rotate(&c_T2, nextangle_current - angle);
	rotate(&c_T11, nextangle_current - angle);
	rotate(&c_T12, nextangle_current - angle);
	rotate(&c_T21, nextangle_current - angle);
	rotate(&c_T22, nextangle_current - angle);
	rotate(&c_T111, nextangle_current - angle);
	rotate(&c_T112, nextangle_current - angle);
	rotate(&c_T121, nextangle_current - angle);
	rotate(&c_T122, nextangle_current - angle);
	rotate(&c_T211, nextangle_current - angle);
	rotate(&c_T212, nextangle_current - angle);
	rotate(&c_T221, nextangle_current - angle);
	rotate(&c_T222, nextangle_current - angle);

	if (nextangle_target == nextangle_current) {
	    pathlength = pathmax;
	    angle = nextangle_target;
	}
    }

    // Current line you are on
    _led->colour_set(_led->colour_green);
    _led->line(c_start, c_target);

    // Next turn
    _led->colour_set(_led->colour_blue);
    _led->line(c_T1, c_target);
    _led->line(c_T2, c_target);

    // Next next turn
    _led->colour_set(_led->colour_yellow);
    _led->line(c_T11, c_T1);
    _led->line(c_T12, c_T1);
    _led->line(c_T21, c_T2);
    _led->line(c_T22, c_T2);

    // Next next next turn
    _led->colour_set(_led->colour_magenta);
    _led->line(c_T111, c_T11);
    _led->line(c_T112, c_T11);
    _led->line(c_T121, c_T12);
    _led->line(c_T122, c_T12);
    _led->line(c_T211, c_T21);
    _led->line(c_T212, c_T21);
    _led->line(c_T221, c_T22);
    _led->line(c_T222, c_T22);

    _led->dot(c_center, _led->colour_red);
    _led->dot(c_target, _led->colour_cyan);

    if (nextangle_target == nextangle_current) {
	pathlength--;
	if (pathlength == 0) {
	    nextangle_current = angle;
	    nextangle_target = angle + angleturn * (random() % 2 == 0 ? -1 : 1);
	}
    }


}
