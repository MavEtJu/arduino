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
    broken = 0;
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
    clear_colourmap();
    add_colourmap(' ' , 0,   0,   0); // real black
    add_colourmap('.' , 1,   1,   1); // black
    add_colourmap('W' , 8,   8,   8); // white
    add_colourmap('y' , 8,   8,   0); // yellow
    add_colourmap('G' , 0,   8,   0); // green
    add_colourmap('R' , 8,   0,   0); // red
    add_colourmap('B' , 0,   0,   8); // blue
    add_colourmap('r' , 6,   2,   2); // brown
    add_colourmap('m' , 8,   0,   8); // magenta
    add_colourmap('c' , 0,   8,   8); // cyan
}

LED_Slideshow::~LED_Slideshow(void)
{
    if (images != NULL) {
        free(images);
    }
}

void
LED_Slideshow::clear_colourmap(void)
{
    colourmax = 0;
}

void
LED_Slideshow::add_colourmap(unsigned char c, uint8_t r, uint8_t g, uint8_t b)
{
    colourmap[colourmax] = c;
    colours[colourmax] = _led->Color(r, g, b);
    colourmax++;
}

LED
LED_Slideshow::find_colourmap(unsigned char c)
{
    for (uint8_t i = 0; i < colourmax; i++) {
        if (colourmap[i] == c)
            return colours[i];
    }
    SERIAL4(F("Colour not found: ."), (int)c,
	    F(". - colourmax:"), colourmax
    );
    return _led->Color(255, 255, 255);
}

void
LED_Slideshow::set_imgs(uint8_t _nrs)
{
    nrs = _nrs;
    imgnrs = 0;
    images = (struct SlideshowImage *)malloc(nrs * sizeof(struct SlideshowImage));
    imgnr = 0;
}


void
LED_Slideshow::add_image(uint16_t width, uint16_t bits, const char *img)
{
    //SERIAL2(F("Loading image "), imgnrs);
    if (imgnrs >= nrs)
	return;
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
    SERIAL2(F("imgnr: "), imgnr);

#ifdef DEBUG_MEMORY
    FREEMEMORY("freememory before display: ");
    delay(50);
#endif
    display(&images[imgnr]);
#ifdef DEBUG_MEMORY
    FREEMEMORY("freememory after display: ");
#endif
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

#ifdef DEBUG_MEMORY
    FREERAM("LED_Slideshow::display");
    FREEMEMORY("freememory in display()");
    delay(50);
#endif
   
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
#ifdef DEBUG_MEMORY
	FREEMEMORY("malloc done for in");
#endif
        if (in == NULL) {
            SERIAL3(F("in = NULL for "), len, F(" bytes"));
#ifdef DEBUG_MEMORY
            FREERAM("in = NULL");
            FREEMEMORY("in = NULL");
            delay(100);
#endif
	    broken = 1;
            return;
        }

	memcpy_P(in, img->image, len);

#ifdef DEBUG_MEMORY
        FREERAM("LED_Slideshow::display:before new");
#endif

        enc = new StringEncodeMulti();
        if (enc == NULL) {
            SERIAL1(F("enc = NULL"));
#ifdef DEBUG_MEMORY
            FREERAM("in = NULL");
            FREEMEMORY("in = NULL");
#endif
            free(in);
            delay(100);
	    broken = 1;
            return;
        }
        memset(ps, '\0', sizeof(ps));
#ifdef DEBUG_MEMORY
	FREEMEMORY("new done");
        FREERAM("LED_Slideshow::display:before decode");
#endif
        enc->decode(in, ps, img->bits, &imglen, sizeof(ps) - 1);
	if (imglen == 0) {
	    SERIAL1(F("enc->decode returned 0, broken!"));
	    free(in);
	    delete(enc);
	    broken = 1;
	    return;
	}
#ifdef DEBUG_MEMORY
        FREERAM("LED_Slideshow::display:after decode");

	FREEMEMORY("decode done");
	SERIAL2(F("imglen: "), imglen);
#endif
        delete(enc);
#ifdef DEBUG_MEMORY
	FREEMEMORY("delete done");
#endif
	free(in);
#ifdef DEBUG_MEMORY
	FREEMEMORY("free");
	delay(50);
#endif

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
