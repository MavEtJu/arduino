
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
class LED_spaceinvaders1 : public LED_Animation {
    public:
    LED_spaceinvaders1(void);
    void destroy(void);
    void animation(void);
    const char **imgs;
    LED colours[LED_spaceinvaders_IMGS];
    uint8_t width[LED_spaceinvaders_IMGS];
};

void LED_spaceinvaders1::destroy(void)
{
    // Serial.println("LED_spaceinvaders::destroy");
    free(imgs);
}

LED_spaceinvaders1::LED_spaceinvaders1(void) : LED_Animation()
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
LED_spaceinvaders1::animation(void)
{
    uint8_t imgnr = (step / 100) % LED_spaceinvaders_IMGS;
    char ch[256];
    strcpy_P(ch, imgs[imgnr]);
    led.blob(step % (VIEW_WIDTH + 24) - 12, 1, width[imgnr], strlen(ch) / width[imgnr], ch, colours[imgnr]);
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

    static uint16_t phasenr = 5;
    static unsigned long started = 0;
    
    /* testing */
    #define TESTING
    #undef TESTING
    #ifdef TESTING    
    static LED_mario1 *p = new LED_mario1();
    p->loop();
    led.display();
    started++;
    Serial.println(started);
    return;
    #endif
    
//  Serial.print(started);
//  Serial.print(" ");
//  Serial.println(millis());
    
    if (started == 0 || started + 20l * 1000l < millis()) {
        Serial.print(F("Free Memory before free: "));
        Serial.println(freeMemory());
        if (phase[0] != NULL) {
            phase[0]->destroy();
            delete(phase[0]);
            phase[0] = NULL;
        }
        Serial.print(F("Free Memory after free: "));
        Serial.println(freeMemory());
        switch (++phasenr % 10) {
            #define NEW_ANIMATION(t)    { t *p = new t(); phase[0] = p; break; }
            case  0: NEW_ANIMATION(LED_led00_blink1)
            case  1: NEW_ANIMATION(LED_quickbrowfox1)
            case  2: NEW_ANIMATION(LED_spaceinvaders1)
            case  3: NEW_ANIMATION(LED_sinus1);
            case  4: NEW_ANIMATION(LED_sinus2);
            case  5: NEW_ANIMATION(LED_lineshorver1)
            case  6: NEW_ANIMATION(LED_squares1)
            case  7: NEW_ANIMATION(LED_mario1)
            case  8: NEW_ANIMATION(LED_torch1)
            case  9: NEW_ANIMATION(LED_torch2)
        }
        
        Serial.print(F("Free Memory after new: "));
        Serial.println(freeMemory());
        started = millis();
    }
    if (phase[0] != NULL)
        phase[0]->loop();
 
    led.display();
}
