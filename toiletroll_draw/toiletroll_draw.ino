
#include <Arduino.h>
#include <MemoryFree.h>
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

// ==============================
class LED_Animation {
public:
    LED_Animation(void);
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
void LED_Animation::destroy(void)
{
    // Serial.println("LED_Animation::~LED_Animation");
}
void
LED_Animation::loop(void)
{
    step++;
    animation();
    delay(delayms);
}
void
LED_Animation::animation(void)
{
    // Nothing yet
}

// ==============================
class LED_led00_blink : public LED_Animation {
    void animation(void);
};

void
LED_led00_blink::animation(void)
{
    led.dot(0, 0, led.colour_random());
}

// ==============================
class LED_quickbrowfox : public LED_Animation {
    void animation(void);
};

void
LED_quickbrowfox::animation(void)
{
    const char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = led.text_width(s);
    uint16_t i = step % (w + 2 * VIEW_WIDTH);
    led.text(VIEW_WIDTH - i, 2, s, led.colour_magenta);
}

// ==============================
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

        led.dot(m, s, led.colour_yellow);
        led.dot((m + VIEW_WIDTH / 3) % VIEW_WIDTH, s, led.colour_blue);
        led.dot((m + 2 * VIEW_WIDTH / 3) % VIEW_WIDTH, s, led.colour_green);
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

        led.dot(m, s + VIEW_HEIGHT / 2, led.colour_yellow);
    }
}

// ==============================
#define LED_spaceinvaders_IMGS 9
class LED_spaceinvaders : public LED_Animation {
    public:
    LED_spaceinvaders(void);
    void destroy(void);
    void animation(void);
    const char **imgs;
    LED colours[LED_spaceinvaders_IMGS];
    uint8_t width[LED_spaceinvaders_IMGS];
};

void LED_spaceinvaders::destroy(void)
{
    // Serial.println("LED_spaceinvaders::destroy");
    free(imgs);
}

LED_spaceinvaders::LED_spaceinvaders(void) : LED_Animation()
{
    delayms = 150;
    
    colours[0] = led.colour_green;
    colours[1] = led.colour_blue;
    colours[2] = led.colour_magenta;
    colours[3] = led.colour_yellow;
    colours[4] = led.colour_magenta;
    colours[5] = led.colour_cyan;
    colours[6] = led.colour_red;
    colours[7] = led.colour_green;
    colours[8] = led.colour_magenta;

    imgs = (const char **)malloc(sizeof(char *) * LED_spaceinvaders_IMGS);

    // From https://0.s3.envato.com/files/69626951/space-invaders-icons-set-colour-prev.jpg

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
void
LED_spaceinvaders::animation(void)
{
    uint8_t imgnr = (step / 100) % LED_spaceinvaders_IMGS;
    char ch[256];
    strcpy_P(ch, imgs[imgnr]);
    led.blob(step % (VIEW_WIDTH + 24) - 12, 1, width[imgnr], strlen(ch) / width[imgnr], ch, colours[imgnr]);
}

//===========================
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

    step++;
}

struct coal {
	int16_t x, y;
        int16_t intensity;
};
typedef struct coal coal;
void
led_torch1(void)
{
    static uint32_t step = 0;
    static LED colour_floor = led.Color(8 << 2, 4, 0);
    #define COALS 10 * VIEW_WIDTH
    static coal coals[COALS];
    static byte init = 0;

    if (init == 0) {
	init = 1;
	for (uint8_t c = 0; c < COALS; c++) {
	    coals[c].x = 0;
	    coals[c].y = 1;
	}
    }

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

    step++;
}

void
led_torch2(void)
{
    static uint32_t step = 0;
    
    #define COALS VIEW_WIDTH
    static coal coals[COALS];
    static byte init = 0;

    if (init == 0) {
	init = 1;
	for (uint8_t c = 0; c < COALS; c++) {
	    coals[c].x = 0;
	    coals[c].y = - (random() % VIEW_HEIGHT);
            coals[c].intensity = VIEW_HEIGHT << 2 + 2 - (random() % 5);
	}
    }

    // Change in intensity of the lowest level
    static uint32_t piece = 360 / (4 * VIEW_WIDTH);
    uint16_t o = step;
    float f = piece * M_PI / 180 * o;
    float s = sin(f) * VIEW_HEIGHT;
    uint8_t floor_intensity = (VIEW_HEIGHT << 1) + s;
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
    step++;
}

void
setup(void)
{
    Serial.begin(9600);
    pinMode(PIN_BLINK, OUTPUT);
    Serial.print(F("free1: "));
    Serial.println(freeMemory());
    led.view(VIEW_WIDTH, VIEW_HEIGHT);
    led.start();
    Serial.print(F("free2: "));
    Serial.println(freeMemory());
}

LED_Animation *phase[1] = {NULL};
void
loop(void)
{
    loop_blink();
    led.clear();

    static uint16_t phasenr = 0;
    static unsigned long started = 0;
    
    /* testing */
    /*
    static LED_sinus2 *p = new LED_sinus2();
    p->loop();
    led.display();
    started++;
    return;
    */
    
    if (started == 0 || started + 3 * 1000 < millis()) {
        Serial.print(F("Free Memory before free: "));
        Serial.println(freeMemory());
        if (phase[0] != NULL) {
            phase[0]->destroy();
            delete(phase[0]);
            phase[0] = NULL;
        }
        Serial.print(F("Free Memory after free: "));
        Serial.println(freeMemory());
        switch (++phasenr % 5) {
            case 0: { LED_led00_blink *p = new LED_led00_blink(); phase[0] = p; break; } 
            case 1: { LED_quickbrowfox *p = new LED_quickbrowfox(); phase[0] = p; break; } 
            case 2: { LED_spaceinvaders *p = new LED_spaceinvaders(); phase[0] = p; break; }
            case 3: { LED_sinus1 *p = new LED_sinus1(); phase[0] = p; break; }
            case 4: { LED_sinus2 *p = new LED_sinus2(); phase[0] = p; break; }

        }
        Serial.print(F("Free Memory after new: "));
        Serial.println(freeMemory());
        started = millis();
    }
    if (phase[0] != NULL)
        phase[0]->loop();
 
    /* 
    led.dot(1,1,led.colour_random()); led.display();
    led.dot(1,1,led.colour_red);
    */
    
  
//    led_lines_horver();
//    led_squares_growing();
//    led_mario();
//    led_torch1();
//    led_torch2();

    led.display();
}
