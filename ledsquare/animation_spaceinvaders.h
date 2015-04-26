#ifndef animations_spaceinvaders__h
#define animations_spaceinvaders__h

#include "A_Tools.h"
#include "LED_Animation.h"

#define LED_spaceinvaders1_IMGS 11
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
    LED colours[LED_spaceinvaders1_IMGS];
    uint8_t width[LED_spaceinvaders1_IMGS];
    uint8_t encbits[LED_spaceinvaders1_IMGS];
};

#define LED_spaceinvaders2_IMGS 10
class LED_spaceinvaders2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_spaceinvaders2);
    void destroy(void);
    void animation(void);

    StringEncodePlain *enc;
    const char **imgs;
    char imga[128], imgb[128];
    uint16_t imglen;
    int16_t x;
    uint8_t imgnr;
    LED colours[LED_spaceinvaders2_IMGS];
    uint8_t width[LED_spaceinvaders2_IMGS];
    uint8_t encbits[LED_spaceinvaders2_IMGS];
};

#endif
