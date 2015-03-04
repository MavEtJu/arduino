
#include <Arduino.h>
#include "LED_Animation.h"
#include "LED_Text.h"
#include "StringEncode.h"
#include "animations.h"

// ==============================

void
LED_led00_blink1::animation(void)
{
    _led->dot(0, 0, _led->colour_random());
}

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
        if (delayms / 20 > LED_cross1_history - i - 1) {
            continue;
        }
        _led->line(c1[i], c2[i], c[i]);
    }
    
    delayms = 50 + 45 * sin(step / 180.0 * M_PI);
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

void
LED_lineshorver1::animation(void)
{
    int m = step % (2 * _VIEW_HEIGHT);

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

// ============================

LED_squares1::LED_squares1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT) {
    c = _led->colour_random();
}

void
LED_squares1::animation(void)
{
    int m = step % (2 * _VIEW_HEIGHT);

    if (m == 0)
	c = _led->colour_random();
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

// ====================

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
        if (height == _VIEW_HEIGHT / 5 || height == _VIEW_HEIGHT / 2)
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

    imgs = (const char **)malloc(sizeof(char *) * LED_spaceinvaders_IMGS);

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
	Serial.print("imgnr:");
	Serial.print(imgnr);
	Serial.print(" - width:");
	Serial.print(width[imgnr]);
	Serial.print(" - imglen:");
	Serial.println(imglen);
#endif
    }

    height = imglen / width[imgnr];

    _led->blob(x++, 2, width[imgnr], height, img, colours[imgnr]);
}

// =======================

LED_torch1::LED_torch1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    colour_floor = _led->Color(9 << 2, 4, 0);

    numcoals = 32;
    coals = (struct coal *)malloc(numcoals * sizeof(coals));

    for (uint8_t c = 0; c < numcoals; c++) {
        coals[c].x = 0;
        coals[c].y = 1;
    }
}

LED_torch1::~LED_torch1(void)
{
    free(coals);
}

void
LED_torch1::animation(void)
{
    for (uint8_t c = 0; c < numcoals; c++) {
	// There is a 50% chance that a light goes higher
	if (random() % 100 > 66) {
	    // Back to the beginning
	    coals[c].x = random() % _VIEW_WIDTH;
	    coals[c].y = 1;
	} else {
	    coals[c].y++;
	}
	_led->dot(coals[c].x % _VIEW_WIDTH, coals[c].y,
	    _led->Color((_VIEW_HEIGHT - coals[c].y) << 2, _VIEW_HEIGHT - coals[c].y > 1, 0));
    }
    _led->line(0, 0, _VIEW_WIDTH, 0, colour_floor);
}

// ===============

LED_torch2::LED_torch2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{    
    numcoals = 30;
    coals = (struct coal *)malloc(numcoals * sizeof(struct coal));
    
    for (uint8_t c = 0; c < numcoals; c++) {
        coals[c] = new_coal(_VIEW_HEIGHT, 1);
    }
}

struct coal
LED_torch2::new_coal(uint8_t intensity, int randomy)
{
    struct coal c;
    c.x = random() % _VIEW_WIDTH;
    c.y = randomy ? random() % _VIEW_HEIGHT : 0;
    c.intensity = intensity + 2 - (random() % 5);;
    c.decay = random() % 4 + 2;
    return c;
}

LED_torch2::~LED_torch2(void)
{
    free(coals);
}

void
LED_torch2::animation(void)
{
    // Change in intensity of the lowest level
    uint32_t piece = 360 / (4 * _VIEW_WIDTH);
    uint16_t o = step;
    float f = piece * M_PI / 180 * o;
    float s = sin(f) * _VIEW_HEIGHT;
    uint8_t floor_intensity = (_VIEW_HEIGHT << 1) + (int)s;
    LED colour_floor = _led->Color(floor_intensity, floor_intensity, 0);
       
    for (uint8_t c = 0; c < numcoals; c++) {
        coals[c].y++;
        coals[c].intensity -= coals[c].decay;
        if (coals[c].y == _VIEW_HEIGHT || coals[c].intensity <= 0) {
            coals[c] = new_coal(floor_intensity, 0);
        }

        int16_t x = coals[c].x;
        int16_t y = coals[c].y;
        _led->dot(x % _VIEW_WIDTH, y,
            _led->Color(coals[c].intensity, coals[c].intensity, 0));

        /* Spark around the flame */
        if (coals[c].intensity > 2) {
            LED colour_spark = _led->Color(2, 2, 0);
            colour_spark = _led->Color(2, 2, 0);
            if (y > 0) {
                _led->dot(x - 1, y, colour_spark);
                _led->dot(x + 1, y, colour_spark);
            }
            if (y > 1)
                _led->dot(x, y - 1, colour_spark);
            _led->dot(x, y + 1, colour_spark);
        }
    }

    _led->line(0, 0, _VIEW_WIDTH, 0, colour_floor);
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
