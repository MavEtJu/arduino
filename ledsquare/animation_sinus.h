#ifndef animation_sinus__h
#define animation_sinus__h

#include "A_Tools.h"

class LED_sinus1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_sinus1);
    void animation(void);
    LED c[3];
};

class LED_sinus2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_sinus2);
    void animation(void);

    int8_t height;
    int8_t direction;
};

class LED_sinus3 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_sinus3);
    void animation(void);
    LED c[2];
};

class LED_sinus4 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_sinus4);
    void animation(void);
    LED c_sinus;
    LED c_background;
};

class LED_sinus5 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_sinus5);
    void animation(void);
    LED c_sinus;
    LED c_background1;
    LED c_background2;
};

#endif
