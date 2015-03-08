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

#define LED_movingsquares2_squares 2
class LED_movingsquares2 : public LED_Animation {
public:
    MYCONSTRUCTOR(LED_movingsquares2);
    void animation(void);
    void init (int num);

    int numsquares;
    uint16_t steps;
    LED c[2];
    int16_t x0[2], y0[2], x1[2], y1[2], dx[2], dy[2], x[2], y[2];
    int16_t size;
};

#define LED_square_splitting_horver	0
#define LED_square_splitting_diagonal	1
class LED_square_splitting : public LED_Animation {
public:
    MYCONSTRUCTOR(LED_square_splitting);
    void init(void);
    void animation(void);

    char type, origin;
    int8_t steps;
    LED c_now, c_previous;
    struct coordinates c0, c;
    struct distance d;
};

#endif
