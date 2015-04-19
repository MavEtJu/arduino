#include <Arduino.h>
#include "LED_Animation.h"
#include "LED_Text.h"
#include "StringEncode.h"
#include "animation_text.h"
#include "A_Tools.h"
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

// ==============================

MYCONSTRUCTOR_ANIMATION(LED_quickbrownfox1)
{
    text = new LED_Text(led);
}

LED_quickbrownfox1::~LED_quickbrownfox1(void)
{
    delete(text);
}

void
LED_quickbrownfox1::animation(void)
{
    const char *s = "the quick brown fox jumped over the lazy dog 0123456789";
    uint16_t w = text->text_width(s);
    uint16_t i = step % (w + 2 * _VIEW_WIDTH);
    text->text(_VIEW_WIDTH - i, 2, s, _led->colour_red);
}

// ==============================

MYCONSTRUCTOR_ANIMATION(LED_textline1)
{
    text = new LED_Text(led);
    delayms = 0;
}

LED_textline1::~LED_textline1(void)
{
    delete(text);
}

void
LED_textline1::animation(void)
{
    const char *s = "love hate white black rain sun air sky dirk arie left right";
    uint16_t w = text->text_width(s);
    uint16_t i = step % (w + 2 * _VIEW_WIDTH);
    text->text(_VIEW_WIDTH - i, 2, s, _led->colour_white);
    _led->square(0, 0, _VIEW_WIDTH / 2, _VIEW_HEIGHT);
    _led->square(_VIEW_WIDTH / 2 + 1, 0, _VIEW_WIDTH - 1, _VIEW_HEIGHT);
}

