
#include <Arduino.h>
#ifdef SIMULATOR
#include <time.h>
#endif
#ifdef MEMORY
#include <MemoryFree.h>
#endif
#include "led_tools.h"
#include "StringEncode.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

#define VIEW_WIDTH   16
#define VIEW_HEIGHT  16

LEDstrip led = LEDstrip(VIEW_WIDTH * VIEW_HEIGHT, PIN_STRIP);

void
loop_blink(void)
{
    // Blink once every eight ticks.
    static byte onoff = 0;
    digitalWrite(PIN_BLINK, (++onoff % 8) == 0 ? HIGH : LOW);
}

// ==============================
class LED_Animation {
public:
    LED_Animation(void);
    virtual ~LED_Animation(void);
    virtual void destroy(void);
    void loop(void);
    virtual void animation(void);
    uint16_t step;
    uint8_t delayms;
};
LED_Animation::LED_Animation(void)
{
    step = 0;
    delayms = 100;
}
LED_Animation::~LED_Animation(void)
{
}
void LED_Animation::destroy(void)
{
    //
}
void
LED_Animation::loop(void)
{
    animation();
    delay(delayms);
    step++;
}
void
LED_Animation::animation(void)
{
    // Nothing yet
}

// ==============================
class LED_led00_blink1 : public LED_Animation {
    void animation(void);
};

void
LED_led00_blink1::animation(void)
{
    led.dot(0, 0, led.colour_random());
}

// ==============================
class LED_quickbrowfox1 : public LED_Animation {
    void animation(void);
};

void
LED_quickbrowfox1::animation(void)
{
    const char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = led.text_width(s);
    uint16_t i = step % (w + 2 * VIEW_WIDTH);
    led.text(VIEW_WIDTH - i, 2, s, led.colour_magenta);
}

// ==============================
class LED_lineshorver1 : public LED_Animation {
    void animation(void);
};

void
LED_lineshorver1::animation(void)
{
    int m = step % (2 * VIEW_HEIGHT);

    led.colour_set(led.colour_magenta);
    if (m < VIEW_HEIGHT)
        led.line(0, m, VIEW_WIDTH, m);
    else
        led.line(m % VIEW_HEIGHT, 0, m % VIEW_HEIGHT, VIEW_WIDTH);
}

// ============================
class LED_lines1 : public LED_Animation {
    public:
    LED_lines1(void);
    void animation(void);
    LED c;
    char dir;
    uint16_t x1, x2, y1, y2;
    int16_t dx1, dx2, dy1, dy2;
    uint16_t x1_final, x2_final, y1_final, y2_final;
};

LED_lines1::LED_lines1(void)
{
    x1 = y1 = 0;
    x2 = VIEW_WIDTH - 1;
    y2 = VIEW_HEIGHT - 1;
    x1_final = x1;
    x2_final = x2;
    y1_final = y1;
    y2_final = y2;
    dir = 0;
    c = led.colour_red;
    delayms = 20;
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
                x1_final = dx1 == 1 ? VIEW_WIDTH - 1 : 0;
                y1_final = dy1 == 1 ? VIEW_HEIGHT - 1 : 0;
                x2_final = x2;
                y2_final = y2;
                break;
            case 1:
                dx1 = dy1 = 0;
                dx2 = x2 == 0 ? 1 : -1;
                dy2 = y2 == 0 ? 1 : -1;
                x1_final = x1;
                y1_final = y1;
                x2_final = dx2 == 1 ? VIEW_WIDTH - 1 : 0;
                y2_final = dy2 == 1 ? VIEW_HEIGHT - 1 : 0;
                break;
            case 2:
                dx1 = x1 == 0 ? 1 : -1;
                dx2 = x2 == 0 ? 1 : -1;
                dy1 = dy2 = 0;
                x1_final = dx1 == 1 ? VIEW_WIDTH - 1 : 0;
                x2_final = dx2 == 1 ? VIEW_WIDTH - 1 : 0;
                y1_final = y1;
                y2_final = y2;
                break;
            case 3:
                dx1 = dx2 = 0;
                dy1 = y1 == 0 ? 1 : -1;
                dy2 = y2 == 0 ? 1 : -1;
                x1_final = x1;
                x2_final = x2;
                y1_final = dy1 == 1 ? VIEW_HEIGHT - 1 : 0;
                y2_final = dy2 == 1 ? VIEW_HEIGHT - 1 : 0;
                break;
            case 4:
                dx1 = x1 == 0 ? 1 : -1;
                dy1 = dx2 = dy2 = 0;
                x1_final = dx1 == 1 ? VIEW_WIDTH - 1 : 0;
                y1_final = y1;
                x2_final = x2;
                y2_final = y2;
                break;
            case 5:
                dy1 = y1 == 0 ? 1 : -1;
                dx1 = dx2 = dy2 = 0;
                x1_final = x1;
                y1_final = dy1 == 1 ? VIEW_HEIGHT - 1 : 0;
                x2_final = x2;
                y2_final = y2;
                break;
            case 6:
                dx2 = x2 == 0 ? 1 : -1;
                dx1 = dy1 = dy2 = 0;
                x1_final = x1;
                y1_final = y1;
                x2_final = dx2 == 1 ? VIEW_WIDTH - 1 : 0;
                y2_final = y2;
                break;
            case 7:
                dy2 = y2 == 0 ? 1 : -1;
                dx1 = dy1 = dx2 = 0;
                x1_final = x1;
                y1_final = y1;
                x2_final = x2;
                y2_final = dy2 == 1 ? VIEW_HEIGHT - 1 : 0;
                break;
        }
    }
    
    x1 += dx1;
    y1 += dy1;
    x2 += dx2;
    y2 += dy2;    
    led.line(x1, y1, x2, y2, c);
}

// ============================
class LED_squares1 : public LED_Animation {
public:
    LED_squares1(void);
    void animation(void);
    LED c;
};

LED_squares1::LED_squares1(void) : LED_Animation() {
    c = led.colour_random();
}

void
LED_squares1::animation(void)
{
    int m = step % (2 * VIEW_HEIGHT);
    
    if (m == 0)
	c = led.colour_random();
    led.colour_set(c);

    if (m < VIEW_HEIGHT) {
        led.line(0, 0, 0, m);
        led.line(0, m, m, m);
        led.line(m, m, m, 0);
        led.line(m, 0, 0, 0);
    } else {
        m %= VIEW_HEIGHT;
        led.line(VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, m);
        led.line(VIEW_HEIGHT - 1, m, m, m);
        led.line(m, m, m, VIEW_HEIGHT - 1);
        led.line(m, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1);
    }
}

// ===================
class LED_sinus1 : public LED_Animation {
    public:
    LED_sinus1(void);
    void animation(void);
};

LED_sinus1::LED_sinus1(void) : LED_Animation()
{
    delayms = 50;
}

void
LED_sinus1::animation(void)
{
    uint32_t piece = 360 / VIEW_WIDTH;

    for (uint16_t m = 0; m < VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * VIEW_HEIGHT / 2 + VIEW_HEIGHT / 2;

        led.dot(m, (int)s, led.colour_yellow);
        led.dot((m + VIEW_WIDTH / 3) % VIEW_WIDTH, (int)s, led.colour_blue);
        led.dot((m + 2 * VIEW_WIDTH / 3) % VIEW_WIDTH, (int)s, led.colour_green);
    }
}

// ==============================
class LED_sinus2 : public LED_Animation {
    public:
    LED_sinus2(void);
    void animation(void);
    
    int8_t height;
    int8_t direction;
};

LED_sinus2::LED_sinus2(void) : LED_Animation()
{
    delayms = 25;
    height = VIEW_HEIGHT / 2;
    direction = -1;
}

void
LED_sinus2::animation(void)
{
    uint32_t piece = 360 / VIEW_WIDTH;
    if (step % 20 == 0) {
        height += direction;
        if (height == VIEW_HEIGHT / 5 || height == VIEW_HEIGHT / 2)
            direction *= -1;
    }

    for (uint16_t m = 0; m < VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * height;

        led.dot(m, (int)s + VIEW_HEIGHT / 2, led.colour_yellow);
    }
}

// ==============================
#define LED_spaceinvaders_IMGS 11
class LED_spaceinvaders1 : public LED_Animation {
    public:
    LED_spaceinvaders1(void);
    void destroy(void);
    void animation(void);
    void decode(char *img, char *dest, uint16_t length);

    StringEncode *enc;
    const char **imgs;
    char img[128];
    uint16_t imglen;
    uint16_t x;
    uint8_t imgnr;
    LED colours[LED_spaceinvaders_IMGS];
    uint8_t width[LED_spaceinvaders_IMGS];
    uint8_t encbits[LED_spaceinvaders_IMGS];
};

void
LED_spaceinvaders1::destroy(void)
{
    free(imgs);
    delete(enc);
}

LED_spaceinvaders1::LED_spaceinvaders1(void) : LED_Animation()
{
    delayms = 150;

    imgnr = 255;

    colours[0] = led.colour_green;
    colours[1] = led.colour_blue;
    colours[2] = led.colour_magenta;
    colours[3] = led.colour_yellow;
    colours[4] = led.colour_magenta;
    colours[5] = led.colour_cyan;
    colours[6] = led.colour_red;
    colours[7] = led.colour_green;
    colours[8] = led.colour_magenta;
    colours[9] = led.colour_green;
    colours[10] = led.colour_white;
    enc = new StringEncode();

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

    if (imgnr > LED_spaceinvaders_IMGS || x == VIEW_WIDTH) {
	uint16_t encbytes;
	char in[16];

	imgnr++;
	imgnr %= LED_spaceinvaders_IMGS;

	encbytes = 1 + encbits[imgnr] / 8;
	memcpy_P(in, imgs[imgnr], encbytes);
	enc->DecodePlain(in, img, encbits[imgnr], &imglen);

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

    led.blob(x++, 2, width[imgnr], height, img, colours[imgnr]);
}

//===========================
class LED_mario1 : public LED_Animation {
public:
    LED_mario1(void);
    void animation(void);
    LED colours[6];
    const char *img;
    char ps[257];
    uint8_t COLOUR_RED, COLOUR_SKIN, COLOUR_BROWN, COLOUR_BLACK, COLOUR_BLUE, COLOUR_YELLOW;
};

LED_mario1::LED_mario1(void) : LED_Animation()
{
    /*
     * R red
     * S skin
     * B brown
     * b black
     * l blue
     * y yellow
     *
     */
    img = PSTR(
        "     RRRRRR     "
        "    RRRRRRRRRR  "
        "    BBBSSSbS    "
        "   BSBSSSSbSSS  "
        "   BSBSSSSSbSSS "
        "   BBSSSSSbbbb  "
        "     SSSSSSSS   "
        "    RRlRRRl     "
        "   RRRlRRlRRR   "
        "  RRRRllllRRRR  "
        "  SSRlyllylRSS  "
        "  SSSllllllSSS  "
        "  SSllllllllSS  "
        "    lll  lll    "
        "   BBBB  BBBB   "
        "  BBBBB  BBBBB  "
    );
    COLOUR_RED =	0;
    COLOUR_SKIN =	1;
    COLOUR_BROWN =	2;
    COLOUR_BLACK =	3;
    COLOUR_BLUE =	4;
    COLOUR_YELLOW =	5;
    colours[COLOUR_RED   ] = led.Color(244 >> 4,   0 >> 4,  10 >> 4);
    colours[COLOUR_SKIN  ] = led.Color(208 >> 4, 189 >> 4, 156 >> 4);
    colours[COLOUR_BROWN ] = led.Color( 92 >> 4,  68 >> 4,  30 >> 4);
    colours[COLOUR_BLACK ] = led.Color( 26 >> 4,  26 >> 4,  26 >> 4);
    colours[COLOUR_BLUE  ] = led.Color( 84 >> 4,  45 >> 4, 214 >> 4);
    colours[COLOUR_YELLOW] = led.Color(225 >> 4, 202 >> 4,  47 >> 4);
    
    strcpy_P(ps, img);
}

void
LED_mario1::animation(void)
{
    for (uint8_t y = 0; y < 16; y++) {
	for (uint8_t x = 0; x < 16; x++) {
	    LED c = led.colour_black;
	    switch (ps[y * 16 + x]) {
	    case 'R': c = colours[COLOUR_RED   ]; break;
	    case 'S': c = colours[COLOUR_SKIN  ]; break;
	    case 'B': c = colours[COLOUR_BROWN ]; break;
	    case 'b': c = colours[COLOUR_BLACK ]; break;
	    case 'l': c = colours[COLOUR_BLUE  ]; break;
	    case 'y': c = colours[COLOUR_YELLOW]; break;
	    }

//	    led.dot((x + step) % VIEW_HEIGHT, VIEW_HEIGHT - y, c);
	    led.dot(x , VIEW_HEIGHT - 1 - y, c);
	}
    }
}

// =======================
struct coal {
	int16_t x, y;
        int16_t intensity;
};
typedef struct coal coal;
#define COALS VIEW_WIDTH

class LED_torch1 : public LED_Animation {
    public:
    LED colour_floor;

    coal coals[COALS];
    
    LED_torch1(void);
    void animation(void);
};

LED_torch1::LED_torch1(void)
{
    colour_floor = led.Color(9 << 2, 4, 0);
    
    for (uint8_t c = 0; c < COALS; c++) {
        coals[c].x = 0;
        coals[c].y = 1;
    }
}

void
LED_torch1::animation(void)
{
    for (uint8_t c = 0; c < COALS; c++) {
	// There is a 50% chance that a light goes higher
	if (random() % 100 > 66) {
	    // Back to the beginning
	    coals[c].x = random() % VIEW_WIDTH;
	    coals[c].y = 1;
	} else {
	    coals[c].y++;
	}
	led.dot(coals[c].x % VIEW_WIDTH, coals[c].y,
	    led.Color((VIEW_HEIGHT - coals[c].y) << 2, VIEW_HEIGHT - coals[c].y > 1, 0));
    }
    led.line(0, 0, VIEW_WIDTH, 0, colour_floor);
}

// ===============
class LED_torch2 : public LED_Animation {
public:
    LED_torch2(void);
    void animation(void);
    coal coals[COALS];
};

LED_torch2::LED_torch2(void)
{
    for (uint8_t c = 0; c < COALS; c++) {
	coals[c].x = random() % VIEW_WIDTH;
	coals[c].y = - (random() % VIEW_HEIGHT);
        coals[c].intensity = VIEW_HEIGHT << 1;
    }
}

void
LED_torch2::animation(void)
{   
    // Change in intensity of the lowest level
    uint32_t piece = 360 / (4 * VIEW_WIDTH);
    uint16_t o = step;
    float f = piece * M_PI / 180 * o;
    float s = sin(f) * VIEW_HEIGHT;
    uint8_t floor_intensity = (VIEW_HEIGHT << 1) + (int)s;
    LED colour_floor = led.Color(floor_intensity, floor_intensity, 0);

    for (uint8_t c = 0; c < COALS; c++) {
        coals[c].y++;
        coals[c].intensity -= (random() % 2) + 1;
        if (coals[c].y == VIEW_HEIGHT || coals[c].intensity <= 0) {
            coals[c].y = 0;
            coals[c].x = random() % VIEW_WIDTH;
            coals[c].intensity = floor_intensity + 2 - (random() % 5);
        }

        int16_t x = coals[c].x;
        int16_t y = coals[c].y;
        led.dot(x % VIEW_WIDTH, y,
            led.Color(coals[c].intensity, coals[c].intensity, 0));

        /* Spark around the flame */
        if (coals[c].intensity > 2) {
            LED colour_spark = led.Color(2, 2, 0);
            colour_spark = led.Color(2, 2, 0);
            if (y > 0) {
                led.dot(x - 1, y, colour_spark);
                led.dot(x + 1, y, colour_spark);
            }
            if (y > 1)
                led.dot(x, y - 1, colour_spark);
            led.dot(x, y + 1, colour_spark);
        }
    }
    
    led.line(0, 0, VIEW_WIDTH, 0, colour_floor);
}

void
setup(void)
{
#ifdef SIMULATOR
    srandom(time(NULL));
#else
    randomSeed(analogRead(0));
#endif
#ifdef SERIAL
    Serial.begin(9600);
# ifdef MEMORY
#  ifndef SIMULATOR
    Serial.print(F("free1: "));
    Serial.println(freeMemory());
#  endif
# endif
#endif
    pinMode(PIN_BLINK, OUTPUT);
#ifdef SIMULATOR
    led.view(VIEW_WIDTH, VIEW_HEIGHT, 0);
#else
    led.view(VIEW_WIDTH, VIEW_HEIGHT, VIEW_SQUARE);
#endif
    led.start();
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
    Serial.print(F("free2: "));
    Serial.println(freeMemory());
#  endif
# endif
#endif
}

LED_Animation *phase[1] = {NULL};

void
loop(void)
{
    loop_blink();
    led.clear();

    static uint16_t phasenr = 5;
    static unsigned long started = 0;
    
    /* testing */
#define TESTING
//#undef TESTING
#ifdef TESTING    
    static LED_lines1 *p = new LED_lines1();
    p->loop();
    led.display();
    started++;
# ifdef SERIAL
    Serial.println(started);
# endif
    return;
#endif
    
    if (started == 0 || started + 30l * 1000l < millis()) {
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory before free: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif
        if (phase[0] != NULL) {
            phase[0]->destroy();
            delete(phase[0]);
            phase[0] = NULL;
        }
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory after free: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif
        switch (++phasenr % 10) {
            #define NEW_ANIMATION(t)    { t *p = new t(); phase[0] = p; break; }
            case  0: NEW_ANIMATION(LED_led00_blink1)
            case  1: NEW_ANIMATION(LED_quickbrowfox1)
            case  2: NEW_ANIMATION(LED_spaceinvaders1)
            case  3: NEW_ANIMATION(LED_sinus1);
            case  4: NEW_ANIMATION(LED_sinus2);
            case  5: NEW_ANIMATION(LED_lineshorver1)
            case  6: NEW_ANIMATION(LED_squares1)
            case  7: NEW_ANIMATION(LED_torch1)
            case  8: NEW_ANIMATION(LED_mario1)
            case  9: NEW_ANIMATION(LED_torch2)
        }
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory after new: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif
        started = millis();
    }
    if (phase[0] != NULL)
        phase[0]->loop();
 
    led.display();
}
