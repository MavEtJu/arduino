#ifndef animations__h
#define animations__h

#include "animation_squares.h"
#include "animation_lines.h"
#include "animation_torches.h"

class LED_test : public LED_Animation {
    public:
    PARENTCONSTRUCTOR(LED_test);
    void animation(void);
};

class LED_led00_blink1 : public LED_Animation {
    public:
    PARENTCONSTRUCTOR(LED_led00_blink1);
    void animation(void);
};

class LED_quickbrowfox1 : public LED_Animation {
    public:
    MYOWNCONSTRUCTOR(LED_quickbrowfox1);
    ~LED_quickbrowfox1(void);
    void animation(void);
    LED_Text *text;
};

class LED_sinus1 : public LED_Animation {
    public:
    MYOWNCONSTRUCTOR(LED_sinus1);
    void animation(void);
};

class LED_sinus2 : public LED_Animation {
    public:
    MYOWNCONSTRUCTOR(LED_sinus2);
    void animation(void);

    int8_t height;
    int8_t direction;
};

#define LED_spaceinvaders_IMGS 11
class LED_spaceinvaders1 : public LED_Animation {
    public:
    MYOWNCONSTRUCTOR(LED_spaceinvaders1);
    void destroy(void);
    void animation(void);

    StringEncodePlain *enc;
    const char **imgs;
    char img[128];
    uint16_t imglen;
    uint16_t x;
    uint8_t imgnr;
    LED colours[LED_spaceinvaders_IMGS];
    uint8_t width[LED_spaceinvaders_IMGS];
    uint8_t encbits[LED_spaceinvaders_IMGS];
};

class LED_plasma1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_plasma1);
    ~LED_plasma1(void);
    void animation(void);
    int numcolours;
    LED *colourmap;
};

#endif
