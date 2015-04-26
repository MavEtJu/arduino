#ifndef LED_Slideshow__h
#define LED_Slideshow__h

#include "LED_Strip.h"

struct SlideshowImage {
    uint16_t width;
    uint16_t bits;
    const char *image;
};

#define LED_Slideshow_MAX    30
class LED_Slideshow {
public:
    LED_Slideshow(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    virtual ~LED_Slideshow(void);
    virtual void display(struct SlideshowImage *img);
    virtual void destroy(void);
    virtual void create_colourmap(void);
    void clear_colourmap(void);
    void add_colourmap(unsigned char c, uint8_t r, uint8_t g, uint8_t b);
    LED find_colourmap(unsigned char c);
    void loop(void);

    struct SlideshowImage *images;
    uint8_t imgnr, imgnrs, nrs;

    LED colours[LED_Slideshow_MAX];
    uint8_t colourmap[LED_Slideshow_MAX];

    void add_image(uint16_t width, uint16_t bits, const char *img);
    void set_imgs(uint8_t nrs);
    char shown;
    LED_Strip *_led;
    uint16_t _VIEW_HEIGHT;
    uint16_t _VIEW_WIDTH;
    uint8_t broken;
    uint8_t colourmax;
};

#endif
