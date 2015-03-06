
#ifndef LED_Animation__h
#define LED_Animation__h

#include "LED_Strip.h"

// ==============================
class LED_Animation {
public:
    LED_Animation(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    virtual ~LED_Animation(void);
    virtual void destroy(void);
    void loop(void);
    virtual void animation(void);
    uint16_t step;
    uint8_t delayms;
    uint16_t _VIEW_HEIGHT, _VIEW_WIDTH;
    int16_t _sVIEW_HEIGHT, _sVIEW_WIDTH;
    LED_Strip *_led;
    uint8_t broken;
};

#endif
