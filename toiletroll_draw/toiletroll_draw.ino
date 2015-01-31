#include "led_tools.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

#define VIEW_WIDTH  20
#define VIEW_HEIGHT  7

LED led = LED(144, PIN_STRIP);

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
    led.text(VIEW_WIDTH - i, 0, s, led.colour_red);

    step++;
    step %= 300;
    led.display();
    delay(100);
    return;

    if (step < 100) {
        led.colour_set(step % 2 == 0 ? led.colour_red : led.colour_cyan);
        if (step % 14 < 7) {
            led.line(0, step % 7, 10, 6 - (step % 7));
        } else {
            led.line(6 - step % 7, 0, step % 7, 6);
        }
    } else if (step < 200) {
        int m = step % 14;
        if (m < 7)
            led.line(0, m, 19, m);
        else
            led.line(m % 7, 0, m % 7, 6);
    } else if (step < 300) {
        int m = step % 14;
        if (m < 7) {
            led.line(0, 0, 0, m, led.colour_green);
            led.line(0, m, m, m);
            led.line(m, m, m, 0);
            led.line(m, 0, 0, 0);
        } else {
            m %= 7;
            led.line(6, 6, 6, m, led.colour_green);
            led.line(6, m, m, m);
            led.line(m, m, m, 6);
            led.line(m, 6, 6, 6);

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
