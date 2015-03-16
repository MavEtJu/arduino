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
