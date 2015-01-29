#include "led_tools.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

LED led = LED(144, PIN_STRIP);

void
setup(void)
{
    led.start();
}

void
loop(void)
{
    led.colour_set(led.Color(0, 0, 8));
    led.colour_o1_o2(15, 18);
    
    led.colour_o1_o2(3, 6, led.Color(8, 0, 0));
    led.colour_o1_o2(9, 12);
    led.colour_o_length(60, 3, led.Color(0, 8, 0));
    led.colour_o_length(80, 3);
    led.show();
    delay(25);
}


