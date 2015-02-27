
#ifndef LED_Text__h
#define LED_Text__h

#include "led_tools.h"

// ==============================
class LED_Text {
public:
    LED_Text(LEDstrip *LEDstrip);
    ~LED_Text(void);
    void letters_init(void);

    void text(int16_t x, int16_t y, const char *string, LED dotcolour);
    uint16_t text_width(const char *string);

    const char **letters;
    LEDstrip *_led;

};

#endif
