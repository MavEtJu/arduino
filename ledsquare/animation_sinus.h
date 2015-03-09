#ifndef animation_sinus__h
#define animation_sinus__h

#include "A_Tools.h"

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

#endif
