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
    led.dot(0, 0, led.colour_random());
    
    char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = led.text_width(s);
    uint16_t i = step % (w + 2 * VIEW_WIDTH);
    led.text(VIEW_WIDTH - i, 0, s, led.colour_purple);

    step++;
    led.display();
    delay(100);
    return;

    if (step < 200) {
        int m = step % VIEW_HEIGHT;
        led.colour_set(led.colour_purple);
        if (m < VIEW_HEIGHT)
            led.line(0, m, VIEW_WIDTH, m);
        else
            led.line(m % VIEW_HEIGHT, 0, m % VIEW_HEIGHT, VIEW_WIDTH);
    } else if (step < 300) {
        int m = step % (2 * VIEW_HEIGHT);
        if (m < VIEW_HEIGHT) {
            led.line(0, 0, 0, m, led.colour_green);
            led.line(0, m, m, m);
            led.line(m, m, m, 0);
            led.line(m, 0, 0, 0);
        } else {
            m %= VIEW_HEIGHT;
            led.line(VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, m, led.colour_green);
            led.line(VIEW_HEIGHT - 1, m, m, m);
            led.line(m, m, m, VIEW_HEIGHT - 1);
            led.line(m, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1, VIEW_HEIGHT - 1);

        }
    }

    step++;
    step %= 300;
    led.display();
    delay(1000);
}

void
loop_blink(void)
{
    // Blink once every eight ticks.
    static byte onoff = 0;
    digitalWrite(PIN_BLINK, (++onoff % 8) == 0 ? HIGH : LOW);
}
