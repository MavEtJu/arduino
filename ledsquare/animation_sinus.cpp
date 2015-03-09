#include <Arduino.h>
#include "LED_Animation.h"
#include "animation_sinus.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

LED_sinus1::LED_sinus1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    delayms = 50;
}

void
LED_sinus1::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;

    for (uint16_t m = 0; m < _VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * _VIEW_HEIGHT / 2 + _VIEW_HEIGHT / 2;

        _led->dot(m, (int)s, _led->colour_yellow);
        _led->dot((m + _VIEW_WIDTH / 3) % _VIEW_WIDTH, (int)s, _led->colour_blue);
        _led->dot((m + 2 * _VIEW_WIDTH / 3) % _VIEW_WIDTH, (int)s, _led->colour_green);
    }
}

// ==============================

LED_sinus2::LED_sinus2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
{
    delayms = 25;
    height = VIEW_HEIGHT / 2;
    direction = -1;
}

void
LED_sinus2::animation(void)
{
    uint32_t piece = 360 / _VIEW_WIDTH;
    if (step % 20 == 0) {
        height += direction;
        if (height == _sVIEW_HEIGHT / 5 || height == _sVIEW_HEIGHT / 2)
            direction *= -1;
    }

    for (uint16_t m = 0; m < _VIEW_WIDTH; m++) {
        uint16_t o = m + step;
        float f = piece * M_PI / 180 * o;
        float s = sin(f) * height;

        _led->dot(m, (int)s + _VIEW_HEIGHT / 2, _led->colour_yellow);
    }
}
