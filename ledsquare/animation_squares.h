#ifndef animations_squares__h
#define animations_squares__h

#include "LED_Animation.h"
#include "A_Tools.h"

class LED_squares1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_squares1);
    void animation(void);
    LED c;
};

#define LED_squares2_history 20
class LED_squares2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_squares2);
    void animation(void);
    struct area a[LED_squares2_history];
    LED c[LED_squares2_history], c_last;
    void shift_history(struct area a, LED c);
};

#define LED_squares3_history 4
class LED_squares3 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_squares3);
    void animation(void);
    struct coordinates cs[LED_squares3_history], c, max;
    LED colours[LED_squares3_history], colour;
    void shift_history(struct coordinates c, LED colour);
    int dx, dy;
    uint16_t steps;
    virtual void draw(int div);
};

class LED_squares3a : public LED_squares3 {
public:
    PARENTCONSTRUCTOR2(LED_squares3a, LED_squares3);
    void draw(int div);
};
class LED_squares3b : public LED_squares3 {
public:
    PARENTCONSTRUCTOR2(LED_squares3b, LED_squares3);
    void draw(int div);
};
class LED_squares3c : public LED_squares3 {
public:
    PARENTCONSTRUCTOR2(LED_squares3c, LED_squares3);
    void draw(int div);
};

#define LED_movingsquares1_squares 4
class LED_movingsquares1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_movingsquares1);
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
    MYOWNCONSTRUCTOR(LED_movingsquares2);
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
    MYOWNCONSTRUCTOR(LED_square_splitting);
    void init(void);
    void animation(void);

    char type, origin;
    int8_t steps;
    LED c_now, c_previous;
    struct coordinates c0, c;
    struct distance d;
};

#define LED_spinningsquares1_squares	8
#define LED_spinningsquares1_history	8
struct LED_spinningsquares1_data {
    struct coordinates c1, c2, c;
    int dx, dy;
    LED colour;
};
class LED_spinningsquares1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_spinningsquares1);
    struct LED_spinningsquares1_data data[LED_spinningsquares1_squares];
    struct coordinates history[LED_spinningsquares1_squares][LED_spinningsquares1_history];
    void animation(void);
    void history_shift(int i, struct coordinates c);
};

class LED_squares4 : public LED_Animation {
public:
    PARENTCONSTRUCTOR(LED_squares4);
    void animation(void);
    int16_t y;
};


#endif
