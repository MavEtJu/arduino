#include <Arduino.h>
#include "led_tools.h"
#include "LED_Slideshow.h"

LED_Slideshow::LED_Slideshow(LEDstrip *led, uint16_t VIEW_HEIGHT)
{
    imgnr = 0;
    shown = 0;
    imgs = NULL;
    create_colourmap();
    _led = led;
    _VIEW_HEIGHT = VIEW_HEIGHT;
}

void
LED_Slideshow::create_colourmap(void)
{
    memset(&colourmap, 0, sizeof(colourmap));

    /*
     * . black
     * W white
     * R red
     * G green
     * B blue
     * y yellow
     * r brown
     * m magenta
     */
    add_colourmap(' ' , COLOUR_REALBLACK,     0,   0,   0);
    add_colourmap('.' , COLOUR_BLACK,         1,   1,   1);
    add_colourmap('W' , COLOUR_WHITE,         8,   8,   8);
    add_colourmap('y' , COLOUR_YELLOW,        8,   8,   0);
    add_colourmap('G' , COLOUR_GREEN,         0,   8,   0);
    add_colourmap('R' , COLOUR_RED,           8,   0,   0);
    add_colourmap('B' , COLOUR_BLUE,          0,   0,   8);
    add_colourmap('r' , COLOUR_BROWN,         6,   2,   2);
    add_colourmap('m' , COLOUR_MAGENTA,       8,   0,   8);
    add_colourmap('c' , COLOUR_CYAN,          0,   8,   8);
}

LED_Slideshow::~LED_Slideshow(void)
{
    if (imgs != NULL)
        free(imgs);
}

void
LED_Slideshow::add_colourmap(char c, uint8_t v, uint8_t r, uint8_t g, uint8_t b)
{
    colourmap[v] = c;
    colours[v] = _led->Color(r, g, b);
}

LED
LED_Slideshow::find_colourmap(char c)
{
    for (uint8_t i = 0; i < LED_Slideshow_MAX; i++) {
        if (colourmap[i] == c)
            return colours[i];
    }
    return _led->Color(255, 255, 255);
}

void
LED_Slideshow::set_imgs(uint8_t nrs)
{
    imgnrs = nrs;
    imgs = (const char **)malloc(sizeof(const char *) * imgnrs);
}

void LED_Slideshow::destroy(void)
{
}

void
LED_Slideshow::loop(void)
{
    if (shown)
        display();
    shown = 1;
    delay(1000);
    imgnr++;
    imgnr %= imgnrs;
}

void
LED_Slideshow::display(void)
{
    char ps[257];
    strcpy_P(ps, imgs[imgnr]);

    for (uint8_t y = 0; y < 16; y++) {
	for (uint8_t x = 0; x < 16; x++) {
	    LED c = find_colourmap(ps[y * 16 + x]);
	    _led->dot(x, _VIEW_HEIGHT - 1 - y, c);
	}
    }
}

