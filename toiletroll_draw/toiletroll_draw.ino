#include <Arduino.h>
#include "led_tools.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

#define VIEW_WIDTH   17
#define VIEW_HEIGHT  14

LEDstrip led = LEDstrip(VIEW_WIDTH * VIEW_HEIGHT, PIN_STRIP);

void
loop_blink(void)
{
    // Blink once every eight ticks.
    static byte onoff = 0;
    digitalWrite(PIN_BLINK, (++onoff % 8) == 0 ? HIGH : LOW);
}

void
led00_blink(void)
{
    led.dot(0, 0, led.colour_random());
}

void
led_text(void)
{
    static uint32_t step = 0;
    const char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = led.text_width(s);
    uint16_t i = step % (w + 2 * VIEW_WIDTH);
    led.text(VIEW_WIDTH - i, 2, s, led.colour_magenta);
    step++;
}

void
led_lines_horver(void)
{
    static uint32_t step = 0;
    int m = step % (2 * VIEW_HEIGHT);

    led.colour_set(led.colour_magenta);
    if (m < VIEW_HEIGHT)
        led.line(0, m, VIEW_WIDTH, m);
    else
        led.line(m % VIEW_HEIGHT, 0, m % VIEW_HEIGHT, VIEW_WIDTH);

    step++;
}

void
led_squares_growing(void)
{
    static uint32_t step = 0;
    int m = step % (2 * VIEW_HEIGHT);
    static LED c = led.colour_black;

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
        led.line(VIEW_HEIGHT - 1, VIEW_HEIGHT - 1,
                 VIEW_HEIGHT - 1, m);
        led.line(VIEW_HEIGHT - 1, m, m, m);
        led.line(m, m, m, VIEW_HEIGHT - 1);
        led.line(m, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1);
    }

    step++;
}

void
led_sinus(void)
{
    static uint32_t step = 0;
    static uint32_t piece = 360 / VIEW_WIDTH;

    for (uint16_t m = 0; m < VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f);
       /* 
        Serial.print("offset: ");
        Serial.print(o);
        Serial.print(" f: ");
        Serial.print(f);
        Serial.print(" s: ");
        Serial.print(s);
        Serial.println("");
*/
        led.dot(m, (VIEW_HEIGHT / 2) + s * (VIEW_HEIGHT / 2),
	    led.colour_yellow);
        led.dot((m + VIEW_WIDTH / 3) % VIEW_WIDTH,
	    (VIEW_HEIGHT / 2) + s * (VIEW_HEIGHT / 2), led.colour_blue);
        led.dot((m + 2 * VIEW_WIDTH / 3) % VIEW_WIDTH,
	    (VIEW_HEIGHT / 2) + s * (VIEW_HEIGHT / 2), led.colour_green);
    }

    step++;
}

void
led_spaceinvaders(void)
{
    #define IMGS 9
    static uint32_t step = 0;
    uint8_t imgnr = (step / 100) % IMGS;
    static const char **imgs = NULL;
    static uint8_t width[IMGS];
    static LED colours[IMGS];

    // From https://0.s3.envato.com/files/69626951/space-invaders-icons-set-colour-prev.jpg
    if (imgs == NULL) {
	colours[0] = led.colour_green;
	colours[1] = led.colour_blue;
	colours[2] = led.colour_magenta;
	colours[3] = led.colour_yellow;
	colours[4] = led.colour_magenta;
	colours[5] = led.colour_cyan;
	colours[6] = led.colour_red;
	colours[7] = led.colour_green;
	colours[8] = led.colour_magenta;

	imgs = (const char **)malloc(sizeof(char *) * IMGS);

	width[0] = 12;
	imgs[0] = PSTR(
	"  X      X  "
	"X  X    X  X"
	"X XXXXXXXX X"
	"XXX XXXX XXX"
	" XXXXXXXXXX "
	"  XXXXXXXX  "
	"  X      X  "
	" XX      XX "
	);

	width[1] = 9;
	imgs[1] = PSTR(
	"  X   X  "
	"   X X   "
	"  XXXXX  "
	" XX X XX "
	"XXXXXXXXX"
	"X XXXXX X"
	"X XXXXX X"
	"   X X   "
	"  XX XX  "
	);

	width[2] = 9;
	imgs[2] = PSTR(
	"   XXX   "
	"  XXXXX  "
	" X  X  X "
	" XXXXXXX "
	"  XXXXX  "
	" X X X X "
	"X       X"
	);

	width[3] = 9;
	imgs[3] = PSTR(
	"  XXXXX  "
	" XXXXXXX "
	"XX  X  XX"
	"XX XX XXX"
	"XXXXXXXXX"
	"XXXXXXXXX"
	"XXXXXXXXX"
	"X X X X X"
	);

	width[4] = 10;
	imgs[4] = PSTR(
	"   XXXX   "
	" XXXXXXXX "
	"XXX XX XXX"
	"XXXXXXXXXX"
	"XXXXXXXXXX"
	"  XX  XX  "
	" XX XX XX "
	"XX      XX"
	);

	width[5] = 9;
	imgs[5] = PSTR(
	"   X X   "
	"X XXXXX X"
	"XXX X XXX"
	" XXXXXXX "
	" X X X X "
	"XX     XX"
	);

	width[6] = 9;
	imgs[6] = PSTR(
	"   X X   "
	"  XXXXX  "
	" XXXXXXX "
	"XX  X  XX"
	"XXXXXXXXX"
	"XXXXXXXXX"
	"X X X X X"
	);

	width[7] = 11;
	imgs[7] = PSTR(
	"  X     X  "
	"   X   X   "
	"  XXXXXXX  "
	" XX XXX XX "
	"XXXXXXXXXXX"
	"X XXXXXXX X"
	"X X     X X"
	"   XX XX   "
	);

	width[8] = 8;
	imgs[8] = PSTR(
	"   XX   "
	"  XXXX  "
	" XXXXXX "
	"XX XX XX"
	"XXXXXXXX"
	"  X  X  "
	" X XX X "
	"X X  X X"
	);
    }
    
    char ch[256];
    strcpy_P(ch, imgs[imgnr]);
    led.blob(step % (VIEW_WIDTH + 24) - 12, 1, width[imgnr], strlen(ch) / width[imgnr], ch, colours[imgnr]);
    
    step++;
}

void
led_mario(void)
{
    static uint32_t step = 0;
    static const char *img = NULL;
    static LED colours[6];
    static char ps[257];

    if (img == NULL) {
	/*
	 * R red
	 " S skin
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
	#define COLOUR_RED	0
	#define COLOUR_SKIN	1
	#define COLOUR_BROWN	2
	#define COLOUR_BLACK	3
	#define COLOUR_BLUE	4
	#define COLOUR_YELLOW	5
	colours[COLOUR_RED   ] = led.Color(244 >> 4,   0 >> 4,  10 >> 4);
	colours[COLOUR_SKIN  ] = led.Color(208 >> 4, 189 >> 4, 156 >> 4);
	colours[COLOUR_BROWN ] = led.Color( 92 >> 4,  68 >> 4,  30 >> 4);
	colours[COLOUR_BLACK ] = led.Color( 26 >> 4,  26 >> 4,  26 >> 4);
	colours[COLOUR_BLUE  ] = led.Color( 84 >> 4,  45 >> 4, 214 >> 4);
	colours[COLOUR_YELLOW] = led.Color(225 >> 4, 202 >> 4,  47 >> 4);
    }

    strcpy_P(ps, img);
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
	    led.dot(x , VIEW_HEIGHT - y, c);
	}
    }

    //

    step++;
}

void
setup(void)
{
    /* Serial.begin(9600); */
    pinMode(PIN_BLINK, OUTPUT);
    led.view(VIEW_WIDTH, VIEW_HEIGHT);
    led.start();
}

void
loop(void)
{
    loop_blink();

    led.clear();
    led00_blink();

    // led_text();
    // led_lines_horver();
    // led_squares_growing();
    led_sinus();	// Needs a delay of 10 ms
    // led_spaceinvaders();
    // led_mario();

    led.display();
    delay(40);
    return;
}
