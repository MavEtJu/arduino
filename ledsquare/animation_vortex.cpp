#include <Arduino.h>
#include "LED_Animation.h"
#include "A_Tools.h"
#include "animation_vortex.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

MYCONSTRUCTOR_ANIMATION(LED_vortex1)
{
    for (int i = 0; i < LED_vortex1_history; i++) {
	colours[i] = _led->colour_black;
    }
}

void
LED_vortex1::animation(void)
{
    for (int i = LED_vortex1_history - 1; i > 0; i--) {
	colours[i] = colours[i - 1];
    }
    colours[0] = _led->colour_transform(step);

    for (int x = 0; x < _sVIEW_WIDTH / 2; x++) {
	_led->square(x, x, _sVIEW_WIDTH - x * 2, _sVIEW_HEIGHT - x * 2,
	    colours[_sVIEW_WIDTH / 2 - x]);
    }
}

// ========================

MYCONSTRUCTOR_ANIMATION(LED_vortex2)
{
    for (int i = 0; i < LED_vortex1_history; i++) {
	colours[i] = _led->colour_black;
    }
}

void
LED_vortex2::animation(void)
{
    for (int i = LED_vortex2_history - 1; i > 0; i--) {
	colours[i] = colours[i - 1];
    }
    colours[0] = _led->colour_transform(step);

    for (int x = 0; x < _sVIEW_WIDTH / 2; x++) {
	_led->colour_set(colours[_sVIEW_WIDTH / 2 - x]);
	_led->horline(x, 0, _VIEW_WIDTH);
	_led->horline(_sVIEW_HEIGHT - 1 - x, 0, _VIEW_WIDTH);
    }
}
