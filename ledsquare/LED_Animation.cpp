#include <Arduino.h>
#include "LED_Animation.h"

LED_Animation::LED_Animation(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT)
{
    step = 0;
    delayms = 100;
    _VIEW_WIDTH = VIEW_WIDTH;
    _VIEW_HEIGHT = VIEW_HEIGHT;
    _sVIEW_WIDTH = (int16_t)VIEW_WIDTH;
    _sVIEW_HEIGHT = (int16_t)VIEW_HEIGHT;
    _led = led;
    broken = 0;
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

