#include <Arduino.h>
#include "LED_Animation.h"
#include "LED_Text.h"
#include "StringEncode.h"
#include "animations.h"
#include "A_Tools.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

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

// ==============================

LED_quickbrowfox1::LED_quickbrowfox1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    text = new LED_Text(led);
}

LED_quickbrowfox1::~LED_quickbrowfox1(void)
{
    delete(text);
}

void
LED_quickbrowfox1::animation(void)
{
    const char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = text->text_width(s);
    uint16_t i = step % (w + 2 * _VIEW_WIDTH);
    text->text(_VIEW_WIDTH - i, 2, s, _led->colour_red);
}

// ==============================

LED_sinus1::LED_sinus1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    delayms = 50;
}

void
LED_sinus1::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;

    for (uint16_t m = 0; m < _VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * _VIEW_HEIGHT / 2 + _VIEW_HEIGHT / 2;

        _led->dot(m, (int)s, _led->colour_yellow);
        _led->dot((m + _VIEW_WIDTH / 3) % _VIEW_WIDTH, (int)s, _led->colour_blue);
        _led->dot((m + 2 * _VIEW_WIDTH / 3) % _VIEW_WIDTH, (int)s, _led->colour_green);
    }
}

// ==============================

LED_sinus2::LED_sinus2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
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
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * height;

        _led->dot(m, (int)s + _VIEW_HEIGHT / 2, _led->colour_yellow);
    }
}

// ==============================

void
LED_spaceinvaders1::destroy(void)
{
    free(imgs);
    delete(enc);
}

LED_spaceinvaders1::LED_spaceinvaders1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    delayms = 150;

    imgnr = 255;

    colours[0] = _led->colour_green;
    colours[1] = _led->colour_blue;
    colours[2] = _led->colour_magenta;
    colours[3] = _led->colour_yellow;
    colours[4] = _led->colour_magenta;
    colours[5] = _led->colour_cyan;
    colours[6] = _led->colour_red;
    colours[7] = _led->colour_green;
    colours[8] = _led->colour_magenta;
    colours[9] = _led->colour_green;
    colours[10] = _led->colour_white;

    enc = new StringEncodePlain();
    if (enc == NULL) {
	SERIAL1(F("enc=NULL in LED_spaceinvaders1"));
	broken = 1;
	return;
    }

    imgs = (const char **)malloc(sizeof(char *) * LED_spaceinvaders_IMGS);
    if (imgs == NULL) {
	SERIAL3(F("imgs=NULL for "), LED_spaceinvaders_IMGS, F("bytes"));
#ifdef DEBUG_MEMORY
	FREERAM("LED_spaceinvaders1: img");
	FREEMEMORY("LED_spaceinvaders1: img");
#endif
	broken = 1;
	delete(enc);
	return;
    }

    // From https://0.s3.envato.com/files/69626951/space-invaders-icons-set-colour-prev.jpg

    width[0] = 12;
    encbits[0] = 96;
    imgs[0] = PSTR(
	/*
	|  X      X  |
	|X  X    X  X|
	|X XXXXXXXX X|
	|XXX XXXX XXX|
	| XXXXXXXXXX |
	|  XXXXXXXX  |
	|  X      X  |
	| XX      XX |
	*/
	"\x20\x49\x09\xbf\xde\xf7\x7f\xe3\xfc\x20\x46\x06"
	);

    width[1] = 9;
    encbits[1] = 81;
    imgs[1] = PSTR(
	/*
	|  X   X  |
	|   X X   |
	|  XXXXX  |
	| XX X XX |
	|XXXXXXXXX|
	|X XXXXX X|
	|X XXXXX X|
	|   X X   |
	|  XX XX  |
	*/
	"\x22\x0a\x0f\x8d\x6f\xfd\xf6\xfa\x28\x36\x00"
	);

    width[2] = 9;
    encbits[2] = 63;
    imgs[2] = PSTR(
	/*
	|   XXX   |
	|  XXXXX  |
	| X  X  X |
	| XXXXXXX |
	|  XXXXX  |
	| X X X X |
	|X       X|
	*/
	"\x1c\x1f\x12\x4f\xe3\xe2\xaa\x02"
	);

    width[3] = 9;
    encbits[3] = 72;
    imgs[3] = PSTR(
	/*
	|  XXXXX  |
	| XXXXXXX |
	|XX  X  XX|
	|XX XX XXX|
	|XXXXXXXXX|
	|XXXXXXXXX|
	|XXXXXXXXX|
	|X X X X X|
	*/
	"\x3e\x3f\xb2\x7b\x7f\xff\xff\xff\x55"
	);

    width[4] = 10;
    encbits[4] = 80;
    imgs[4] = PSTR(
	/*
	|   XXXX   |
	| XXXXXXXX |
	|XXX XX XXX|
	|XXXXXXXXXX|
	|XXXXXXXXXX|
	|  XX  XX  |
	| XX XX XX |
	|XX      XX|
	*/
	"\x1e\x1f\xee\xdf\xff\xff\xcc\xc6\xdb\x03"
	);

    width[5] = 9;
    encbits[5] = 54;
    imgs[5] = PSTR(
	/*
	|   X X   |
	|X XXXXX X|
	|XXX X XXX|
	| XXXXXXX |
	| X X X X |
	|XX     XX|
	*/
	"\x14\x5f\x7a\xef\xe5\x56\x0c"
	);

    width[6] = 9;
    encbits[6] = 63;
    imgs[6] = PSTR(
	/*
	|   X X   |
	|  XXXXX  |
	| XXXXXXX |
	|XX  X  XX|
	|XXXXXXXXX|
	|XXXXXXXXX|
	|X X X X X|
	*/
	"\x14\x1f\x1f\xd9\x3f\xff\xfe\xaa"
	);

    width[7] = 11;
    encbits[7] = 88;
    imgs[7] = PSTR(
	/*
	|  X     X  |
	|   X   X   |
	|  XXXXXXX  |
	| XX XXX XX |
	|XXXXXXXXXXX|
	|X XXXXXXX X|
	|X X     X X|
	|   XX XX   |
	*/
	"\x20\x82\x20\xfe\x37\x6f\xff\x7f\x68\x28\xd8"
	);

    width[8] = 8;
    encbits[8] = 64;
    imgs[8] = PSTR(
	/*
	|   XX   |
	|  XXXX  |
	| XXXXXX |
	|XX XX XX|
	|XXXXXXXX|
	|  X  X  |
	| X XX X |
	|X X  X X|
	*/
	"\x18\x3c\x7e\xdb\xff\x24\x5a\xa5"
	);

    width[9] = 15;
    encbits[9] = 105;
    imgs[9] = PSTR(
	/*
	|       X       |
	|      XXX      |
	|      XXX      |
	| XXXXXXXXXXXXX |
	|XXXXXXXXXXXXXXX|
	|XXXXXXXXXXXXXXX|
	|XXXXXXXXXXXXXXX|
	*/
	"\x01\x00\x07\x00\x0e\x03\xff\xef\xff\xff\xff\xff\xff\x80"
	);

    width[10] = 16;
    encbits[10] = 112;
    imgs[10] = PSTR(
	/*
	|     XXXXXX     |
	|   XXXXXXXXXX   |
	|  XXXXXXXXXXXX  |
	| XX XX XX XX XX |
	|XXXXXXXXXXXXXXXX|
	|  XXX  XX  XXX  |
	|   X        X   |
	*/
	"\x07\xe0\x1f\xf8\x3f\xfc\x6d\xb6\xff\xff\x39\x9c\x10\x08"
	);

}

void
LED_spaceinvaders1::animation(void)
{
    uint8_t height;

    if (imgnr > LED_spaceinvaders_IMGS || x == _VIEW_WIDTH) {
	uint16_t encbytes;
	char in[16];

	imgnr++;
	imgnr %= LED_spaceinvaders_IMGS;

	encbytes = 1 + encbits[imgnr] / 8;
	memcpy_P(in, imgs[imgnr], encbytes);
	enc->decode(in, img, encbits[imgnr], &imglen);

	x = -width[imgnr];

#ifdef SERIAL
	SERIAL6(F("imgnr:"), imgnr, \
		F(" - width:"), width[imgnr], \
		F(" - imglen:"), imglen);
#endif
    }

    height = imglen / width[imgnr];

    _led->blob(x++, 2, width[imgnr], height, img, colours[imgnr]);
}

// =====================================

LED_plasma1::LED_plasma1(LED_Strip *l, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(l, VIEW_WIDTH, VIEW_HEIGHT)
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
