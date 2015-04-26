#include <Arduino.h>
#include "LED_Animation.h"
#include "StringEncode.h"
#include "animations.h"
#include "A_Tools.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

/*
 * +----------------+
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * |     X      X   |
 * |   X  X    X  X |
 * |   X XXXXXXXX X |
 * |   XXX XXXX XXX |
 * |    XXXXXXXXXX  |
 * |     XXXXXXXX   |
 * |     X      X   |
 * |    XX      XX  |
 * |                |
 * |                |
 * |                |
 * +----------------+
 */

MYCONSTRUCTOR_ANIMATION(LED_spaceinvaders1)
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

    imgs = (const char **)malloc(sizeof(char *) * LED_spaceinvaders1_IMGS);
    if (imgs == NULL) {
	SERIAL3(F("imgs=NULL for "), LED_spaceinvaders1_IMGS, F("bytes"));
#ifdef DEBUG_MEMORY
	FREERAM("LED_spaceinvaders1: img");
	FREEMEMORY("LED_spaceinvaders1: img");
#endif
	broken = 1;
	delete(enc);
	return;
    }

    // http://dev.bowdenweb.com/a/fonts/symbols/invaders-from-space/invaders-from-space-font-specimen.jpg

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
LED_spaceinvaders1::destroy(void)
{
    free(imgs);
    delete(enc);
}

void
LED_spaceinvaders1::animation(void)
{
    uint8_t height;

    if (imgnr > LED_spaceinvaders1_IMGS || x == _VIEW_WIDTH) {
	uint16_t encbytes;
	char in[16];

	imgnr++;
	imgnr %= LED_spaceinvaders1_IMGS;

	encbytes = 1 + encbits[imgnr] / 8;
	memcpy_P(in, imgs[imgnr], encbytes);
	enc->decode(in, img, encbits[imgnr], &imglen);

	x = -width[imgnr];

	SERIAL6(F("imgnr:"), imgnr, \
		F(" - width:"), width[imgnr], \
		F(" - imglen:"), imglen);
    }

    height = imglen / width[imgnr];

    _led->blob(x++, 2, width[imgnr], height, img, colours[imgnr]);
}

// ========================

MYCONSTRUCTOR_ANIMATION(LED_spaceinvaders2)
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

    enc = new StringEncodePlain();
    if (enc == NULL) {
	SERIAL1(F("enc=NULL in LED_spaceinvaders2"));
	broken = 1;
	return;
    }

    imgs = (const char **)malloc(sizeof(char *) * 2 * LED_spaceinvaders2_IMGS);
    if (imgs == NULL) {
	SERIAL3(F("imgs=NULL for "), LED_spaceinvaders2_IMGS, F("bytes"));
#ifdef DEBUG_MEMORY
	FREERAM("LED_spaceinvaders2: img");
	FREEMEMORY("LED_spaceinvaders2: img");
#endif
	broken = 1;
	delete(enc);
	return;
    }

    // http://dev.bowdenweb.com/a/fonts/symbols/invaders-from-space/invaders-from-space-font-specimen.jpg

    width[0] = 11;
    encbits[0] = 88;
    imgs[0] = PSTR("\x20\x82\x20\xfe\x37\x6f\xff\x7f\x68\x28\xd8");
    imgs[1] = PSTR("\x20\x92\x26\xfe\xf7\x7f\xfe\xff\x88\x22\x02");

    width[1] = 8;
    encbits[1] = 64;
    imgs[2] = PSTR("\x18\x3c\x7e\xdb\xff\x24\x5a\xa5");
    imgs[3] = PSTR("\x18\x3c\x7e\xdb\xff\x24\x42\x24");

    width[2] = 12;
    encbits[2] = 96;
    imgs[4] = PSTR("\x00\x00\xf0\x7f\xee\x67\xff\xf1\x98\x26\x41\x08");
    imgs[5] = PSTR("\x00\x00\xf0\x7f\xee\x67\xff\xf1\x98\x36\xcc\x03");

    width[3] = 10;
    encbits[3] = 80;
    imgs[6] = PSTR("\x21\x04\x83\xf1\xb6\xff\xef\xd9\x24\x84");
    imgs[7] = PSTR("\x00\x04\x83\xf1\xfe\xed\xef\xd9\x24\xcc");

    width[4] = 7;
    encbits[4] = 56;
    imgs[8] = PSTR("\x82\xfb\x5e\xb7\xd5\x60\xb6");
    imgs[9] = PSTR("\x82\xfb\x5e\xb7\xc5\x11\x41");

    width[5] = 9;
    encbits[5] = 72;
    imgs[10] = PSTR("\x3e\x3f\xb2\x7f\xf1\xc1\x11\x05\x01");
    imgs[11] = PSTR("\x3e\x3f\xb2\x7f\xf1\xc1\x11\x04\x6c");

    width[6] = 10;
    encbits[6] = 80;
    imgs[12] = PSTR("\x21\x04\x83\xf3\xb7\xff\xef\xda\x14\x48");
    imgs[13] = PSTR("\x21\x24\x9b\xf7\xb7\x6d\x9f\xe5\x2b\x03");

    width[7] = 8;
    encbits[7] = 64;
    imgs[14] = PSTR("\x18\x7e\xff\x99\xff\x5a\x42\x3c");
    imgs[15] = PSTR("\x18\x7e\xff\x99\xff\x24\x5a\x81");

    width[8] = 9;
    encbits[8] = 72;
    imgs[16] = PSTR("\x00\x00\x07\x07\xc4\x93\xf8\xa8\xaa");
    imgs[17] = PSTR("\x00\x11\x1f\xd9\x3f\xff\xfe\xaa\xaa");

    width[9] = 8;
    encbits[9] = 64;
    imgs[18] = PSTR("\x24\x7e\xdb\xff\xa5\x99\x81\xc3");
    imgs[19] = PSTR("\x24\x18\xbd\xdb\xff\xbd\x99\xc3");
}

void
LED_spaceinvaders2::destroy(void)
{
    free(imgs);
    delete(enc);
}

void
LED_spaceinvaders2::animation(void)
{
    uint8_t height;

    if (imgnr > LED_spaceinvaders2_IMGS || x == _sVIEW_WIDTH) {
	uint16_t encbytes;
	char in[16];

	imgnr++;
	imgnr %= LED_spaceinvaders2_IMGS;

	encbytes = 1 + encbits[imgnr] / 8;
	memcpy_P(in, imgs[2 * imgnr], encbytes);
	enc->decode(in, imga, encbits[imgnr], &imglen);
	encbytes = 1 + encbits[imgnr] / 8;
	memcpy_P(in, imgs[2 * imgnr + 1], encbytes);
	enc->decode(in, imgb, encbits[imgnr], &imglen);

	x = - width[imgnr];

	SERIAL6(F("imgnr:"), imgnr, \
		F(" - width:"), width[imgnr], \
		F(" - imglen:"), imglen);
    }

    height = imglen / width[imgnr];

    _led->blob(x, 2, width[imgnr], height, (x % 2 == 0) ? imga : imgb, colours[imgnr]);
    x++;
}


