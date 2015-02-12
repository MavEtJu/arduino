#include "led_tools.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

#define VIEW_WIDTH   17
#define VIEW_HEIGHT  14

LEDstrip led = LEDstrip(VIEW_WIDTH * VIEW_HEIGHT, PIN_STRIP);

void
setup(void)
{
    Serial.begin(9600);
    pinMode(PIN_BLINK, OUTPUT);
    led.view(VIEW_WIDTH, VIEW_HEIGHT);
    led.start();
}

void
loop(void)
{
    static uint32_t step = 0;
    
    loop_blink();

    led.clear();
    led00_blink();

    // led_text();
    // led_lines_horver();
    // led_squares_growing();
    led_sinus();
    // led_spaceinvaders();

    led.display();
    delay(10);
    return;
}

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
    char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = led.text_width(s);
    uint16_t i = step % (w + 2 * VIEW_WIDTH);
    led.text(VIEW_WIDTH - i, 2, s, led.colour_purple);
    step++;
}

void
led_lines_horver(void)
{
    static uint32_t step = 0;
    int m = step % VIEW_HEIGHT;

    led.colour_set(led.colour_purple);
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

    if (m < VIEW_HEIGHT) {
        led.line(0, 0, 0, m, led.colour_green);
        led.line(0, m, m, m);
        led.line(m, m, m, 0);
        led.line(m, 0, 0, 0);
    } else {
        m %= VIEW_HEIGHT;
        led.line(VIEW_HEIGHT - 1, VIEW_HEIGHT - 1,
                 VIEW_HEIGHT - 1, m, led.colour_green);
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

    for (uint16_t m = 0; m < VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = 8 * M_PI / 180 * o;
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
        led.dot(m, (VIEW_HEIGHT / 2) + s * (VIEW_HEIGHT / 2), led.colour_yellow);
        led.dot((m + VIEW_WIDTH / 3) % VIEW_WIDTH, (VIEW_HEIGHT / 2) + s * (VIEW_HEIGHT / 2), led.colour_blue);
        led.dot((m + 2 * VIEW_WIDTH / 3) % VIEW_WIDTH, (VIEW_HEIGHT / 2) + s * (VIEW_HEIGHT / 2), led.colour_green);
    }

    step++;
}

void
led_spaceinvaders(void)
{
    static uint32_t step = 0;
    
    #define IMGS 9
    const char **img = (const char **)malloc(sizeof(char *) * IMGS);

    // From https://0.s3.envato.com/files/69626951/space-invaders-icons-set-colour-prev.jpg

    img[0] = PSTR(
    "  X      X  "
    "X  X    X  X"
    "X XXXXXXXX X"
    "XXX XXXX XXX"
    " XXXXXXXXXX "
    "  XXXXXXXX  "
    "  X      X  "
    " XX      XX "
    );
    
    char ch[256];
    strcpy_P(ch, img[0]);
    led.blob(step % (VIEW_WIDTH + 24) - 12, 1, 12, 8, ch, led.colour_green);
    
    step++;
    return;

    img[1] = PSTR(
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

    img[2] = PSTR(
    "   XXX   "
    "  XXXXX  "
    " X  X  X "
    " XXXXXXX "
    "  XXXXX  "
    " X X X X "
    "X       X"
    );

    img[3] = PSTR(
    "  XXXXX  "
    " XXXXXXX "
    "XX  X  XX"
    "XX XX XXX"
    "XXXXXXXXX"
    "XXXXXXXXX"
    "XXXXXXXXX"
    "X X X X X"
    "XXXXXXXXX"
    );

    img[4] = PSTR(
    "   XXXX   "
    " XXXXXXXX "
    "XXX XX XXX"
    "XXXXXXXXXX"
    "XXXXXXXXXX"
    "  XX  XX  "
    " XX XX XX "
    "XX      XX"
    );

    img[5] = PSTR(
    "   X X   "
    "X XXXXX X"
    "XXX X XXX"
    " XXXXXXX "
    " X X X X "
    "XX     XX"
    );

    img[6] = PSTR(
    "   X X   "
    "  XXXXX  "
    " XXXXXXX "
    "XX  X  XX"
    "XXXXXXXXX"
    "XXXXXXXXX"
    "X X X X X"
    );

    img[7] = PSTR(
    "  X     X  "
    "   X   X   "
    "  XXXXXXX  "
    " XX XXX XX "
    "XXXXXXXXXXX"
    "X XXXXXXX X"
    "X X     X X"
    "   XX XX   "
    );

    img[8] = PSTR(
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
