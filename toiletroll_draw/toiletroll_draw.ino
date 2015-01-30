#include "led_tools.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

LED led = LED(144, PIN_STRIP);

void
setup(void)
{
    led.view(20, 7);
    led.start();
}

void
loop(void)
{
    static uint32_t step = 0;
    
    led.clear();

//    if (step == 0) {
        //led.clear(led.colour_blue);
        
        led.colour_set(led.colour_red);
        led.square(step % 20, step % 5, 3, 3, led.colour_red);
 //   }
    #ifdef foo
    if (step == 2) {
        led.colour_set(led.colour_red);
        led.strip_o1_o2(15, 18);
    
        led.strip_o1_o2(3, 6, led.colour_green);
        led.strip_o1_o2(9, 12);
        led.strip_o_length(60, 3, led.colour_red);
        led.strip_o_length(80, 3);
    }
    #endif

    step++;  
    led.display();
    delay(100);
}


