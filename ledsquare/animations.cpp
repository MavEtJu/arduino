#include <Arduino.h>
#include "LED_Animation.h"
#include "StringEncode.h"
#include "animations.h"
#include "A_Tools.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

/* +----------------+
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |................|
 * |................|
 * |................|
 * |XXXXXXXXXXXXXXXX|
 * +----------------+
 */

void
LED_test::animation(void)
{
    LED c = _led->colour_transform(step);
    _led->square(0, 0, _VIEW_WIDTH, _VIEW_HEIGHT, c);

    // Three line red banner
    if (step < _VIEW_HEIGHT + 2) {
	int16_t line = step % (_VIEW_HEIGHT + 2);
	for (int i = 0; i < 3; i++) {
	    _led->horline(line - i, 0, _VIEW_WIDTH, _led->colour_red);
	}
	return;
    }

    // Three line green banner
    if (step < 2 * (_VIEW_HEIGHT + 2)) {
	int16_t line = step % (_VIEW_HEIGHT + 2);
	for (int i = 0; i < 3; i++) {
	    _led->horline(line - i, 0, _VIEW_WIDTH, _led->colour_green);
	}
	return;
    }

    // Three line blue banner
    if (step < 3 * (_VIEW_HEIGHT + 2)) {
	int16_t line = step % (_VIEW_HEIGHT + 2);
	for (int i = 0; i < 3; i++) {
	    _led->horline(line - i, 0, _VIEW_WIDTH, _led->colour_blue);
	}
	return;
    }

    // Three line redish banner
    if (step < 4 * (_VIEW_HEIGHT + 2)) {
	int16_t line = step % (_VIEW_HEIGHT + 2);
	for (int i = 0; i < 3; i++) {
	    _led->horline(line - i, 0, _VIEW_WIDTH, _led->Color(line, 0, 0));
	}
	return;
    }

    // Three line greenish banner
    if (step < 5 * (_VIEW_HEIGHT + 2)) {
	int16_t line = step % (_VIEW_HEIGHT + 2);
	for (int i = 0; i < 3; i++) {
	    _led->horline(line - i, 0, _VIEW_WIDTH, _led->Color(0, line, 0));
	}
	return;
    }

    // Three line blueish banner
    if (step < 6 * (_VIEW_HEIGHT + 2)) {
	int16_t line = step % (_VIEW_HEIGHT + 2);
	for (int i = 0; i < 3; i++) {
	    _led->horline(line - i, 0, _VIEW_WIDTH, _led->Color(0, 0, line));
	}
	return;
    }

    step = 0;

}

// ==============================

void
LED_led00_blink1::animation(void)
{
    _led->dot(0, 0, _led->colour_random());
}

// =====================================

/*
 * +----------------+
 * |XXXXXXXxXxXxXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXxXxXxX.XxXxXx|
 * |XxX.X X X X X X.|
 * |XxXxX.X X X X.Xx|
 * |XXXXXxXxXxXxXxXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXxXxXxXxXxXX|
 * |XxXxX.X X X X.Xx|
 * |XxXxX.X X X X.Xx|
 * |XXXXXxXxXxXxXxXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXXXXXXXXXX|
 * |XXXXXXXxXxXxXXXX|
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_plasma1)
{
    delayms = 20;
    numcolours = 16;
    colourmap = (LED *)malloc(sizeof(LED) * numcolours);
    if (colourmap == NULL) {
	SERIAL3(F("colourmap=NULL in LED_plasma1 for "), numcolours * sizeof(LED), F(" bytes"));
#ifdef DEBUG_MEMORY
	FREERAM("LED_plasma");
	FREEMEMORY("LED_plasma");
#endif
	broken = 1;
	return;
    }
    for (int i = 0; i < numcolours; i++) {
	colourmap[i] = _led->Color(i, i, 0);
    }
}

LED_plasma1::~LED_plasma1(void)
{
    if (colourmap != NULL)
	free(colourmap);
}

void
LED_plasma1::animation(void)
{
    for (uint16_t x = 0; x < _VIEW_WIDTH; x++) {
	for (uint16_t y = 0; y < _VIEW_HEIGHT; y++) {
	    /*
	     * This formula was given during a 31C3 lighting day 2 talk
	     * about demoing on old 8 bit hardware.
	     */
	    // -1.5 ... 1.5 /
	    double d = sin(step - 3 * x) + sin(step + y) / 2;
	    d += 1.5;
	    d *= numcolours / 3.0;
	    _led->dot(x, y, colourmap[int(d)]);

	}
    }
}

// ===========================

MYCONSTRUCTOR_ANIMATION(LED_pascal1)
{
    delayms = 150;
    stone.y = 0;
    stone.x = _VIEW_WIDTH / 2 - 1;
    memset(bottom, '\0', sizeof(bottom));
}

void
LED_pascal1::animation(void)
{
    drawboard();

    stone.y++;
    if (stone.y >= _sVIEW_HEIGHT / 2 + 1) {
    } else if (stone.y > 1) {
	stone.x += random() %2 == 0 ? -1 : 1;
    }
    if (stone.y == _sVIEW_HEIGHT / 2 + 3) {

	bottom[stone.x / 2]++;
	stone.y = 0;
	stone.x = _VIEW_WIDTH / 2 - 1;
    }
    drawstone();
    drawbottom();
}

void
LED_pascal1::drawboard(void)
{
    _led->colour_set(_led->colour_white);
    for (int y = 0; y < _sVIEW_HEIGHT / 2; y++) {
	for (int x = 0; x < y; x++) {
	    _led->dot(_VIEW_WIDTH / 2 - y + 2 * x, _VIEW_HEIGHT - 2 - y);
	}
    }
}

void
LED_pascal1::drawstone(void)
{
    _led->dot(stone.x, _VIEW_HEIGHT - 1- stone.y, _led->colour_red);
}

void
LED_pascal1::drawbottom(void)
{
    for (int x = 0; x < 8; x++) {
	_led->dot(2 *x, 4, _led->Color(bottom[x], 0, 0));
    }
}
