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
