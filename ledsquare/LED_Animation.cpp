#include <Arduino.h>
#include "LED_Animation.h"

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
}
void
LED_Animation::loop(void)
{
    animation();
    delay(delayms);
    step++;
}
void
LED_Animation::animation(void)
{
    // Nothing yet
}

