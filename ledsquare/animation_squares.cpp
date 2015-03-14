#include <Arduino.h>
#include "LED_Animation.h"
#include "A_Tools.h"
#include "animation_squares.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ============================

/*
 * +----------------+
 * |        XXXXXXXX|
 * |        X      X|
 * |        X      X|
 * |        X      X|
 * |        X      X|
 * |        X      X|
 * |        X      X|
 * |        XXXXXXXX|
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_squares1)
{
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

/*
 * +----------------+
 * |XXXXXXXXX       |
 * |      XXX       |
 * |XXXXXXXXXXX     |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * |XXXXXXXXXXX  x  |
 * | XXXX        x  |
 * | XXXX        x  |
 * | XXXX        x  |
 * | X              |
 * | X              |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_squares2)
{
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

/*
 * +----------------+
 * |XXX XXX XXX XXX |
 * |X   X   X   X   |
 * |                |
 * |                |
 * |XXX XXX XXX XXX |
 * |X   X   X   X   |
 * |                |
 * |                |
 * |XXX XXX XXX XXX |
 * |X   X   X   X   |
 * |                |
 * |                |
 * |XXX XXX XXX XXX |
 * |X   X   X   X   |
 * |                |
 * |                |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_squares3)
{
    delayms = 20;
    c.x = 0;
    c.y = 0;
    colour = _led->colour_random_notblack();
    _led->colour_set(colour);
    steps = 0;
}

void
LED_squares3::animation(void)
{
    int div = steps / 100 + 1;

    if (steps % 100 == 0) {
	if (steps == 200) {
	    c.x = 0;
	    c.y = 0;
	    steps = 0;
	    div = 0;
	}

	max.x = (_VIEW_WIDTH >> div) - 1;
	max.y = (_VIEW_HEIGHT >> div )- 1;
	c.x %= _VIEW_WIDTH >> div;
	c.y %= _VIEW_HEIGHT >> div;
	delayms = 20 << div;
    }

    if (c.x == 0 && c.y == 0) {
	dx = 1;
	dy = 0;
    } else if (c.x == max.x && c.y == 0) {
	dx = 0;
	dy = 1;
    } else if (c.x == 0 && c.y == max.y) {
	dx = 0;
	dy = -1;
    } else if (c.x == max.x && c.y == max.y) {
	dx = -1;
	dy = 0;
    }
    c.x += dx;
    c.y += dy;

    // SERIAL7(steps, " ", div, " x,y: ", c.x, ",", c.y);

    shift_history(c, _led->colour_transform(step));
    draw(div);
    steps++;
}

void
LED_squares3::draw(int div)
{
    // nothing
}

void 
LED_squares3::shift_history(struct coordinates coor, LED col)
{
    for (int i = LED_squares3_history - 1; i > 0; i--) {
	cs[i] = cs[i - 1];
	colours[i] = colours[i - 1];
    }
    cs[0] = coor;
    colours[0] = col;
}

// ==========================

/*
 * +----------------+
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |       X       X|
 * |       X       X|
 * |      XX      XX|
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |       X       X|
 * |       X       X|
 * |      XX      XX|
 * +----------------+
 */

void
LED_squares3a::draw(int div)
{
    div = 1 << div;
    for (int y = 0; y < div; y++) {
	for (int x = 0; x < div; x++) {
	    for (int i = LED_squares3_history - 1; i >= 0; i--) {
		_led->dot(x * _VIEW_WIDTH / div + cs[i].x,
			  y * _VIEW_HEIGHT / div + cs[i].y,
			  colours[i]);
	    }
	}
    }
}

// ============================

/*
 * +----------------+
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |       XX       |
 * |     XXXXXX     |
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |X              X|
 * |XXX          XXX|
 * +----------------+
 */

void
LED_squares3b::draw(int div)
{
    div = 1 << div;
    for (int y = 0; y < div; y++) {
	for (int x = 0; x < div; x++) {
	    if ((x + y) % 2 == 0) {
		for (int i = LED_squares3_history - 1; i >= 0; i--) {
		    _led->dot(x * _VIEW_WIDTH / div + cs[i].x,
			      y * _VIEW_HEIGHT / div + cs[i].y,
			      colours[i]);
		}
	    } else {
		for (int i = LED_squares3_history - 1; i >= 0; i--) {
		    _led->dot((x + 1) * _VIEW_WIDTH / div - cs[i].x - 1,
			      y * _VIEW_HEIGHT / div + cs[i].y,
			      colours[i]);
		}
	    }
	}
    }
}

// =======================================

/*
 * +----------------+
 * |XX              |
 * |X               |
 * |X               |
 * |                |
 * |                |
 * |               X|
 * |               X|
 * |              XX|
 * |        XX      |
 * |        X       |
 * |        X       |
 * |                |
 * |                |
 * |       X        |
 * |       X        |
 * |      XX        |
 * +----------------+
 */

void
LED_squares3c::draw(int div)
{
    div = 1 << div;
    for (int y = 0; y < div; y++) {
	for (int x = 0; x < div; x++) {
	    if ((x + y) % 2 == 0) {
		for (int i = LED_squares3_history - 1; i >= 0; i--) {
		    _led->dot(x * _VIEW_WIDTH / div + cs[i].x,
			      y * _VIEW_HEIGHT / div + cs[i].y,
			      colours[i]);
		}
	    } else {
		for (int i = LED_squares3_history - 1; i >= 0; i--) {
		    _led->dot((x + 1) * _VIEW_WIDTH / div - cs[i].x - 1,
			      (y + 1) * _VIEW_HEIGHT / div - cs[i].y -1,
			      colours[i]);
		}
	    }
	}
    }
    steps++;
}

// ========================

/* +----------------+
 * |      X         |
 * |     XXXX       |
 * |     XX  X      |
 * |    X  X  XX    |
 * |   X   X    X   |
 * |   X   X     XX |
 * |  X    X     XXX|
 * | X     XXXXXX X |
 * | X XXXXXX     X |
 * |XXX     X    X  |
 * | XX     X   X   |
 * |   X    X   X   |
 * |    XX  X  X    |
 * |      X  XX     |
 * |       XXXX     |
 * |         X      |
 * +----------------+
 */

void
LED_squares4a::animation(void)
{
    y = step % _VIEW_WIDTH;

    _led->colour_set(_led->colour_white);
    _led->line(0, y, _VIEW_WIDTH - 1, _VIEW_HEIGHT - 1 - y);
    _led->line(_VIEW_WIDTH - 1 - y, 0, y, _VIEW_HEIGHT - 1);

    _led->colour_set(_led->colour_transform(step / 2));
    _led->line(0, y, y, _VIEW_HEIGHT - 1);
    _led->line(y, _VIEW_HEIGHT - 1, _VIEW_WIDTH - 1, _VIEW_HEIGHT - 1 - y);
    _led->line(_VIEW_WIDTH - 1, _VIEW_HEIGHT - 1 - y, _VIEW_WIDTH - 1 - y, 0);
    _led->line(_VIEW_WIDTH - 1 - y, 0, 0, y);
}

// ======================

/*
 * +----------------+
 * |       X        |
 * |       X        |
 * |       X        |
 * |       X       X|
 * |       X     XX |
 * |        X  XX   |
 * |XXXXX   XXX     |
 * |     XXXX       |
 * |       X X      |
 * |       X  X     |
 * |      X    X    |
 * |      X     X   |
 * |     X       X  |
 * |     X        X |
 * |    X          X|
 * |    X           |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_squares4b)
{
    steps = 0;
}

void
LED_squares4b::animation(void)
{
    int angle = (10 * steps) % 360;
    int div = (steps / 100) % 4 + 3;

    _led->colour_set(_led->colour_transform(step / 4));
    for (int a = 0; a < div; a++) {
	double s = 2 * _VIEW_WIDTH * sin((M_PI * (angle + a * 360 / div)) / 180);
	double c = 2 * _VIEW_WIDTH * cos((M_PI * (angle + a * 360 / div)) / 180);
	_led->line(_VIEW_WIDTH / 2, _VIEW_HEIGHT / 2,
		   _VIEW_WIDTH / 2 + s, _VIEW_HEIGHT / 2 + c);
    }

    steps++;
}

// ============================

/*
 * +----------------+
 * |                |
 * |                |
 * |                |
 * |      XXXX      |
 * |      XXXX      |
 * |      XXXX      |
 * |      XXXX      |
 * |                |
 * |                |
 * |       XXX XXXXX|
 * |       XXX XXXXX|
 * |       XXX XXXXX|
 * |           XXXXX|
 * |          XXXXXX|
 * |          XX    |
 * |                |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_movingsquares1)
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
	SERIAL4(F("dx,dy: "), dx[i], F(","), dy[i]);
	*/

	x[i] += dx[i];
	y[i] += dy[i];

	_led->square(x[i], y[i], size[i], size[i], c[i]);
    }
}

// ==============================

/*
 * +----------------+
 * | XXXX    XXXX   |
 * | XxxX    XxxX   |
 * | XxxX    XxxX   |
 * | XXXX    XXXX   |
 * |   XXXX    XXXX |
 * |   XXXX    XXXX |
 * |   XXXX    XXXX |
 * |   XXXX    XXXX |
 * | XXXX    XXXX   |
 * | XxxX    XxxX   |
 * | XxxX    XxxX   |
 * | XXXX    XXXX   |
 * |   XXXX    XXXX |
 * |   XXXX    XXXX |
 * |   XXXX    XXXX |
 * |   XXXX    XXXX |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_movingsquares2)
{
    c[0] = _led->colour_random_notblack();
    c[1] = _led->colour_random_notblack();
    steps = 0;
    numsquares = 16;
}

void
LED_movingsquares2::init(int num)
{
    numsquares = num;
    delayms = 25 * numsquares;

    size = _VIEW_WIDTH / numsquares;
    x0[0] = 0;
    y0[0] = 0;
    x1[0] = size;
    y1[0] = size;
    x[0] = x0[0];
    y[0] = y0[0];
    x0[1] = 0;
    y0[1] = 0;
    x1[1] = size;
    y1[1] = size;
    x[1] = x1[1];
    y[1] = y1[1];
}

void
LED_movingsquares2::animation(void)
{
    /*
     * ....xxxx....xxxx
     * ....xxxx....xxxx
     * ....xxxx....xxxx
     * ....xxxx....xxxx
     * xxxx....xxxx....
     * xxxx....xxxx....
     * xxxx....xxxx....
     * xxxx....xxxx....
     * ....xxxx....xxxx
     * ....xxxx....xxxx
     * ....xxxx....xxxx
     * ....xxxx....xxxx
     * xxxx....xxxx....
     * xxxx....xxxx....
     * xxxx....xxxx....
     * xxxx....xxxx....
     *
     */
    if (steps % 16 == 0) {
	if (numsquares == 2 && steps % 128 == 0) {
	    init(4);
	} else if (numsquares == 4 && steps % 64 == 0) {
	    init(8);
	} else if (numsquares == 8 && steps % 32 == 0) {
	    init(16);
	} else if (numsquares == 16 && steps % 16 == 0) {
	    init(2);
	    c[0] = _led->colour_random_notblack();
	    c[1] = _led->colour_random_notblack();
	    steps = 0;
	}
    }

    for (int i = 0; i < 2; i++) {
	if (x[i] == x0[i] && y[i] == y0[i]) {
	    dx[i] = 1;
	    dy[i] = 0;
	}
	if (x[i] == x1[i] && y[i] == y0[i]) {
	    dx[i] = 0;
	    dy[i] = 1;
	}
	if (x[i] == x0[i] && y[i] == y1[i]) {
	    dx[i] = 0;
	    dy[i] = -1;
	}
	if (x[i] == x1[i] && y[i] == y1[i]) {
	    dx[i] = -1;
	    dy[i] = 0;
	}
    }

    /*
    SERIAL4("x,y: ", x, ",", y);
    SERIAL4("dx,dy: ", dx, ",", dy);
    SERIAL4("x0,y0: ", x0, ",", y0);
    SERIAL4("x1,y1: ", x1, ",", y1);
    SERIAL1("=====");
    */

    for (int i = 0; i < 2; i++) {
	x[i] += dx[i];
	y[i] += dy[i];
    }

    for (int yy = 0; yy < numsquares; yy += 2) {
	for (int xx = 0; xx < numsquares; xx += 2) {
	    for (int i = 0; i < 2; i++) {
		for (int f = 0; f < _sVIEW_WIDTH / (numsquares); f++) {
		    _led->square(
			f + x[i] + (xx + yy % 2) * (_VIEW_WIDTH / numsquares),
			f + y[i] + (xx % 2 + yy) * (_VIEW_HEIGHT / numsquares),
			_VIEW_WIDTH / numsquares - f * 2,
			_VIEW_HEIGHT / numsquares - f * 2,
			_led->colour_fade(c[i], f));
		}
	    }
	}
    }

    steps++;
}

// ==============================

/*
 * +----------------+
 * |XXXXXXXXXXXXX   |
 * |XXXXXXXXXXXX    |
 * |XXXXXXXXXXX     |
 * |XXXXXXXXXX     X|
 * |XXXXXXXXX     XX|
 * |XXXXXXXX     XXX|
 * |XXXXXXX     XXXX|
 * |XXXXXX     XXXXX|
 * |XXXXX     XXXXXX|
 * |XXXX     XXXXXXX|
 * |XXX     XXXXXXXX|
 * |XX     XXXXXXXXX|
 * |X     XXXXXXXXXX|
 * |     XXXXXXXXXXX|
 * |    XXXXXXXXXXXX|
 * |   XXXXXXXXXXXXX|
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_square_splitting)
{
    c_previous = _led->colour_black;
    c_now = _led->colour_black;
    init();
}

void
LED_square_splitting::init(void)
{
    c_previous = c_now;
    c_now = _led->colour_random_notblack();
    if (_led->colour_same(c_previous, c_now))
	c_now = _led->colour_black;

    origin = random() % 8;
    switch (origin) {
    case 0: // bottom left
	c0.x = c0.y = -1;
	d.dx = d.dy = 1;
	type = LED_square_splitting_diagonal;
	break;
    case 1: // bottom right
	c0.x = _VIEW_WIDTH;
	c0.y = -1;
	d.dx = -1;
	d.dy = 1;
	type = LED_square_splitting_diagonal;
	break;
    case 2: // top left
	c0.x = -1;
	c0.y = _VIEW_HEIGHT;
	d.dx = 1;
	d.dy = -1;
	type = LED_square_splitting_diagonal;
	break;
    case 3: // top right
	c0.x = _VIEW_WIDTH;
	c0.y = _VIEW_HEIGHT;
	d.dx = -1;
	d.dy = -1;
	type = LED_square_splitting_diagonal;
	break;
    case 4: // bottom middle
	c0.x = _VIEW_WIDTH / 2;
	c0.y = -1;
	d.dx = 0;
	d.dy = 1;
	type = LED_square_splitting_horver;
	break;
    case 5: // left middle
	c0.x = -1;
	c0.y = _VIEW_HEIGHT / 2;
	d.dx = 1;
	d.dy = 0;
	type = LED_square_splitting_horver;
	break;
    case 6: // right middle
	c0.x = _VIEW_WIDTH;
	c0.y = _VIEW_HEIGHT / 2;
	d.dx = -1;
	d.dy = 0;
	type = LED_square_splitting_horver;
	break;
    case 7: // top middle
	c0.x = _VIEW_WIDTH / 2;
	c0.y = _VIEW_HEIGHT;
	d.dx = 0;
	d.dy = -1;
	type = LED_square_splitting_horver;
	break;
    }

    c = c0;
    steps = 0;
}

void
LED_square_splitting::animation(void)
{
    if (type == LED_square_splitting_diagonal) {

	if (steps == 2 * _sVIEW_WIDTH + 2)
	    init();

	/* Draw diagonal line */
	_led->square(0, 0, _VIEW_WIDTH, _VIEW_HEIGHT, c_previous);
	_led->line(c0, c, c_now);

	if (steps <  _sVIEW_WIDTH + 1)  {
	    c0.x += d.dx;
	    c0.y += d.dy;
	    steps++;
	    return;
	}

	/* Expand diagonal line */
	if (steps < 2 * _sVIEW_WIDTH + 2) {
	    for (int16_t i = 1; i < steps - _sVIEW_WIDTH - 1; i++) {
		if (origin == 0 || origin == 3) {
		    _led->line(c0.x + i, c0.y, c.x + i, c.y);
		    _led->line(c0.x, c0.y + i, c.x, c.y + i);
		} else if (origin == 1 || origin == 2) {
		    _led->line(c0.x + i, c0.y, c.x + i, c.y);
		    _led->line(c0.x - i, c0.y, c.x - i, c.y);
		}
	    }
	    steps++;
	    return;
	}

    }

    if (type  == LED_square_splitting_horver) {

	if (steps == _sVIEW_WIDTH + 1 + _sVIEW_WIDTH / 2)
	    init();

	_led->square(0, 0, _VIEW_WIDTH, _VIEW_HEIGHT, c_previous);
	_led->line(c0, c, c_now);
	_led->line(c0.x == 0 ? _VIEW_WIDTH : _VIEW_WIDTH - c0.x - 1,
		   c0.y == 0 ? _VIEW_HEIGHT : _VIEW_HEIGHT - c0.y - 1,
		   c.x == 0 ? _VIEW_WIDTH : _VIEW_WIDTH - c.x - 1,
		   c.y == 0 ? _VIEW_HEIGHT : _VIEW_HEIGHT - c.y - 1,
		   c_now);

	/* Draw horizontal or vertical lines */
	if (steps <  _sVIEW_WIDTH + 1)  {
	    c0.x += d.dx;
	    c0.y += d.dy;
	    steps++;
	    return;
	}

	/* Expand horizontal or vertical line */
	if (steps < _sVIEW_WIDTH + 2 + _sVIEW_WIDTH / 2) {
	    for (int16_t i = 1; i < steps - _sVIEW_WIDTH - 1; i++) {
		if (origin == 4 || origin == 7) {
		    _led->verline(c0.x - i - 1, 0, _VIEW_HEIGHT);
		    _led->verline(_sVIEW_WIDTH - c0.x + i, 0, _VIEW_HEIGHT);
		} else if (origin == 5 || origin == 6) {
		    _led->horline(c0.y - i - 1, 0, _VIEW_WIDTH);
		    _led->horline(_sVIEW_HEIGHT - c0.y + i, 0, _VIEW_WIDTH);
		}
	    }
	    steps++;
	    return;
	}

	return;

    }

}

// ================================

/*
 * +----------------+
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |         XX     |
 * |      xx..X     |
 * |      xXX.Xx    |
 * |      xXX xx    |
 * |          xx    |
 * |          .xX   |
 * |         ...X   |
 * |        .xxXX   |
 * |       ...xxxx  |
 * |      .xxXXXX   |
 * |     .xxXXXX    |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_spinningsquares1)
{
    delayms = 25;
    for (int i = 0; i < LED_spinningsquares1_squares; i++) {
	data[i].c.x = i;
	data[i].c.y = i;
	data[i].c1.x = i;
	data[i].c1.y = i;
	data[i].c2.x = _VIEW_WIDTH - i - 1;
	data[i].c2.y = _VIEW_HEIGHT - i - 1;
	data[i].dx = 1;
	data[i].dy = 0;
	data[i].colour = _led->colour_random_notblack();

	for (int h = 0; h < LED_spinningsquares1_history; h++) {
	    history[i][h].x = i;
	    history[i][h].y = i;
	}
    }
}

void
LED_spinningsquares1::history_shift(int i, struct coordinates c)
{
    for (int h = LED_spinningsquares1_history - 1; h > 0; h--) {
 	history[i][h] = history[i][h - 1];
    }
    history[i][0].x = c.x;
    history[i][0].y = c.y;
}

void
LED_spinningsquares1::animation(void)
{
    for (int i = 0; i < LED_spinningsquares1_squares; i++) {

	if (data[i].dx == 1 && data[i].dy == 0) {
	    if (data[i].c.x == data[i].c2.x) {
		data[i].dx = 0;
		data[i].dy = 1;
	    }
	} else if (data[i].dx == 0 && data[i].dy == 1) {
	    if (data[i].c.y == data[i].c2.y) {
		data[i].dx = -1;
		data[i].dy = 0;
	    }
	} else if (data[i].dx == -1 && data[i].dy == 0) {
	    if (data[i].c.x == data[i].c1.x) {
		data[i].dx = 0;
		data[i].dy = -1;
	    }
	} else if (data[i].dx == 0 && data[i].dy == -1) {
	    if (data[i].c.y == data[i].c1.y) {
		data[i].dx = 1;
		data[i].dy = 0;
	    }
	}

	data[i].c.x += data[i].dx;
	data[i].c.y += data[i].dy;
	history_shift(i, data[i].c);

	//SERIAL4("x,y: ", history[i][0].x, ",", history[i][0].y);

	for (int h = LED_spinningsquares1_history - 1; h > 0; h--) {
	    _led->dot(history[i][h], _led->colour_fade_seq(data[i].colour, h));
	}
    }
}

