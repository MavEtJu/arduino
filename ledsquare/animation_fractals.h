#ifndef animations_fractals__h
#define animations_fractals__h

#include "A_Tools.h"
#include "LED_Animation.h"

class LED_hilbert1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_hilbert1);
    void animation(void);
    int xy2d(int n, int x, int y);
    void d2xy(int n, int d, int *x, int *y);
    void rot(int n, int *x, int *y, int rx, int ry);
};

class LED_tree1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_tree1);
    void next(struct coordinates in, struct coordinates *out1, struct coordinates *out2, int angle, int angleturn, int len);
    void prev(struct coordinates out, struct coordinates *in, int prevangle, int len);
    void rotate(struct coordinates *c, int angle);
    void animation(void);

    struct coordinates c_center;

    int16_t prevangle;		// Previous orientiation
    int16_t currangle;		// Current orientiation
    int16_t currangle_turn;	// Turn factor at the end of the line

    int8_t pathlength;
    int8_t pathmax;
};

class LED_tree2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_tree2);
    void next(struct coordinates in, struct coordinates *out1, struct coordinates *out2, int angle, int angleturn, int len);
    void prev(struct coordinates out, struct coordinates *in, int prevangle, int len);
    void rotate(struct coordinates *c, int angle);
    void drawnext(struct coordinates c_T1, int pathlength, int currangle, int turnangle, LED c, double m);
    void animation(void);

    struct coordinates c_offset, c_start;

    int16_t currangle;		// Current orientiation
    int16_t turnangle;		// Turn factor at the end of the line
    int16_t prevturn;		// Turn factor at the end of the line

    int8_t pathlength;
    int8_t pathmax;
};

#endif
