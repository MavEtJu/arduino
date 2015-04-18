#ifndef animations_vortex__h
#define animations_vortex__h

#include "LED_Animation.h"
#include "A_Tools.h"

#define LED_vortex1_history	16
class LED_vortex1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_vortex1);
    void animation(void);
    LED colours[LED_vortex1_history];
};

#define LED_vortex2_history	16
class LED_vortex2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_vortex2);
    void animation(void);
    LED colours[LED_vortex2_history];
};

#endif
