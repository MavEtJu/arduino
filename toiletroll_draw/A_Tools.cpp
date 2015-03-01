//
//

#include <Arduino.h>
#include "LED_Strip.h"

/* https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory */
int
freeRam(void)
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

