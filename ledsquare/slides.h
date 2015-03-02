
#ifndef slides__h
#define slides__h

#include "LED_Slideshow.h"

class LED_mario1 : public LED_Slideshow {
public:
    LED_mario1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
};

class LED_galaga1 : public LED_Slideshow {
public:
    LED_galaga1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
};

class LED_minecraft1 : public LED_Slideshow {
    public:
    LED_minecraft1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void create_colourmap(void);
};

#endif
