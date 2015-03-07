#ifndef animations_squares__h
#define animations_squares__h

#include "LED_Animation.h"
#include "A_Tools.h"

class LED_squares1 : public LED_Animation {
public:
    MYCONSTRUCTOR(LED_squares1);
    void animation(void);
    LED c;
};

#define LED_squares2_history 20
class LED_squares2 : public LED_Animation {
public:
    MYCONSTRUCTOR(LED_squares2);
    void animation(void);
    struct area a[LED_squares2_history];
    LED c[LED_squares2_history], c_last;
    void shift_history(struct area a, LED c);
};

#define LED_movingsquares1_squares 4
class LED_movingsquares1 : public LED_Animation {
public:
    MYCONSTRUCTOR(LED_movingsquares1);
    void animation(void);
    LED c[LED_movingsquares1_squares];
    int16_t x0[LED_movingsquares1_squares], y0[LED_movingsquares1_squares];
    int16_t x1[LED_movingsquares1_squares], y1[LED_movingsquares1_squares];
    int16_t dx[LED_movingsquares1_squares], dy[LED_movingsquares1_squares];
    int16_t size[LED_movingsquares1_squares];
    int16_t x[LED_movingsquares1_squares], y[LED_movingsquares1_squares];
};

#endif
