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
    for (int i = 0; i < LED_vortex2_history; i++) {
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

// ============================

MYCONSTRUCTOR_ANIMATION(LED_vortex3)
{
    for (int i = 0; i < LED_vortex3_history; i++) {
	colours[i] = _led->colour_black;
    }
}

void
LED_vortex3::animation(void)
{
    for (int i = LED_vortex3_history - 1; i > 0; i--) {
	colours[i] = colours[i - 1];
    }
    colours[0] = _led->colour_transform(step);

    for (int x = 0; x < _sVIEW_WIDTH / 2; x++) {
	_led->colour_set(colours[_sVIEW_WIDTH / 2 - x]);
	_led->verline(x, 0, _VIEW_HEIGHT);
	_led->verline(_sVIEW_WIDTH - 1 - x, 0, _VIEW_HEIGHT);
    }
}

// ============================

MYCONSTRUCTOR_ANIMATION(LED_vortex4)
{
    for (int i = 0; i < LED_vortex4_history; i++) {
	colours[i] = _led->colour_black;
    }
}

void
LED_vortex4::animation(void)
{
    for (int i = LED_vortex4_history - 1; i > 0; i--) {
	colours[i] = colours[i - 1];
    }
    colours[0] = _led->colour_transform(step);

    for (int x = 0; x < _sVIEW_WIDTH * 2; x++) {
	_led->colour_set(colours[x]);
	_led->line(x, 0, x - _VIEW_WIDTH, _VIEW_HEIGHT);
    }
}

// ============================

MYCONSTRUCTOR_ANIMATION(LED_vortex5)
{
    for (int i = 0; i < LED_vortex5_history; i++) {
	colours[i] = _led->colour_black;
    }
}

void
LED_vortex5::animation(void)
{
    for (int i = LED_vortex5_history - 1; i > 0; i--) {
	colours[i] = colours[i - 1];
    }
    colours[0] = _led->colour_transform(step);

    int h2 = _VIEW_WIDTH / 2;
    for (int x = 0; x < _sVIEW_WIDTH / 2; x++) {
	_led->colour_set(colours[x]);

	_led->line(x, 0, x - h2, h2);
	_led->line(_VIEW_WIDTH - 1 - x, 0, _VIEW_WIDTH - 1 - (x - h2), h2);
	_led->line(x, _VIEW_WIDTH - 1, x - h2, _VIEW_WIDTH - 1 - h2);
	_led->line(_VIEW_WIDTH - 1 - (x), _VIEW_WIDTH - 1,
		   _VIEW_WIDTH - 1 - (x - h2), _VIEW_WIDTH - 1 - h2);
    }
    for (int x = 1; x < _sVIEW_WIDTH / 2; x++) {
	_led->colour_set(colours[_sVIEW_WIDTH - x]);
	_led->line(h2 - 1, h2 - x, h2 - x, h2 - 1);
	_led->line(_VIEW_WIDTH - (h2 - 1) - 1, h2 - x,
		   _VIEW_WIDTH - (h2 - x) - 1, h2 - 1);
	_led->line(h2 - 1, _VIEW_HEIGHT - (h2 - x) - 1,
		   h2 - x, _VIEW_HEIGHT - (h2 - 1) - 1);
	_led->line(_VIEW_WIDTH - (h2 - 1) - 1, _VIEW_HEIGHT - (h2 - x) - 1,
		   _VIEW_WIDTH - (h2 - x) - 1, _VIEW_HEIGHT - (h2 - 1) - 1);
    }

}
