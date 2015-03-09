#ifndef animations__h
#define animations__h

#include "A_Tools.h"

struct coal {
	int16_t x, y;
        int16_t intensity;
        int decay;
};

class LED_torch1 : public LED_Animation {
    public:
    MYOWNCONSTRUCTOR(LED_torch1);
    ~LED_torch1(void);
    void animation(void);
    
    LED colour_floor;
    int numcoals;
    struct coal *coals;
};

class LED_torch2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_torch2);
    ~LED_torch2(void);
    
    struct coal new_coal(uint8_t intensity, int randomy);
    void animation(void);
    int numcoals;
    struct coal *coals;
};

#endif
