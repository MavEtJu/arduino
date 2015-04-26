#ifndef animations__h
#define animations__h

#include "animation_fractals.h"
#include "animation_lines.h"
#include "animation_sinus.h"
#include "animation_spaceinvaders.h"
#include "animation_squares.h"
#include "animation_text.h"
#include "animation_torches.h"
#include "animation_vortex.h"

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

class LED_plasma1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_plasma1);
    ~LED_plasma1(void);
    void animation(void);
    int numcolours;
    LED *colourmap;
};

class LED_pascal1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_pascal1);
    void animation(void);
    void drawboard(void);
    void drawstone(void);
    void drawbottom(void);
    uint8_t bottom[8];
    struct coordinates stone;
};

#endif
