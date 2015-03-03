#include <Arduino.h>
#include <MemoryFree.h>
#include "LED_Strip.h"
#include "LED_Slideshow.h"
#include "StringEncode.h"
#include "A_Tools.h"


LED_Slideshow::LED_Slideshow(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT)
{
    imgnr = 0;
    shown = 0;
    images = NULL;
    create_colourmap();
    _led = led;
    _VIEW_HEIGHT = VIEW_HEIGHT;
    _VIEW_WIDTH = VIEW_WIDTH;
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
    if (images != NULL) {
        free(images);
    }
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
    imgnrs = 0;
    images = (struct SlideshowImage *)malloc(nrs * sizeof(struct SlideshowImage));
    imgnr = 0;
}


void
LED_Slideshow::add_image(uint16_t width, uint16_t bits, const char *img)
{
    //Serial.print(F("Loading image "));
    //Serial.println(imgnrs);
    images[imgnrs].width = width;
    images[imgnrs].bits = bits;
    images[imgnrs].image = img;
    imgnrs++;
}


void LED_Slideshow::destroy(void)
{
}

void
LED_Slideshow::loop(void)
{
    if (shown)
	delay(1000);
    shown = 1;
    //Serial.print(F("imgnr: "));
    //Serial.println(imgnr);

    //FREEMEMORY(F("freememory before display: "));
    //delay(50);
    display(&images[imgnr]);
    //FREEMEMORY(F("freememory after display: "));
    imgnr++;
    imgnr %= imgnrs;
}

void
LED_Slideshow::display(struct SlideshowImage *img)
{
    char ps[257];
    uint8_t W, H;
    uint16_t imglen;
    StringEncodeMulti *enc;

    //FREERAM(F("LED_Slideshow::display"));
    //FREEMEMORY(F("freememory in display()"));
    //delay(50);
   
    if (img->bits == 0) {
	// Simple bitmap image 16x16
	strcpy_P(ps, img->image);
	W = 16;
	H = 16;
    } else {
	char *in;
        unsigned char c;
	uint16_t len;

	// alphabet size counter
	len = 1;
	// alphabet size
	memcpy_P(&c, img->image, 1);
	len += c;
	// bits in the image
	len += img->bits / 8 + (img->bits % 8 == 0 ? 0 : 1);

        in = (char *)malloc(len * sizeof(char));
	//FREEMEMORY(F("malloc done for in"));
        if (in == NULL) {
            Serial.print(F("in = NULL for "));
            Serial.print(len);
            Serial.println(F(" bytes"));
            FREERAM(F("in = NULL"));
            FREEMEMORY(F("in = NULL"));
            delay(100);
            return;
        }

	memcpy_P(in, img->image, len);

        //FREERAM(F("LED_Slideshow::display:before new"));

        enc = new StringEncodeMulti();
        if (enc == NULL) {
            Serial.println(F("enc = NULL"));
            FREERAM(F("in = NULL"));
            FREEMEMORY(F("in = NULL"));
            free(in);
            delay(100);
            return;
        }
        memset(ps, '\0', sizeof(ps));
	//FREEMEMORY(F("new done"));
        //FREERAM(F("LED_Slideshow::display:before decode"));
        enc->decode(in, ps, img->bits, &imglen, sizeof(ps) - 1);
        //FREERAM(F("LED_Slideshow::display:after decode"));

	//FREEMEMORY(F("decode done"));
	//Serial.print("imglen: ");
	//Serial.println(imglen);
        delete(enc);
	//FREEMEMORY(F("delete done"));
	free(in);
	//FREEMEMORY(F("free"));
	//delay(50);

	W = img->width;
	H = imglen / W;
    }

    uint8_t xoffset = (_VIEW_WIDTH - W) / 2;
    uint8_t yoffset = (_VIEW_HEIGHT - H) / 2;
    for (uint8_t y = 0; y < H; y++) {
	for (uint8_t x = 0; x < W; x++) {
	    LED c = find_colourmap(ps[y * W + x]);
	    _led->dot(xoffset + x, _VIEW_HEIGHT - 1 - y - yoffset, c);
	}
    }
    return;
}