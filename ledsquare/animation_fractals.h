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
    void rotate(struct coordinates *c, int angle);
    void animation(void);

    struct coordinates c_center;
    int16_t angle;		// Current orientiation
    int16_t angleturn;		// Turn factor at the end of the line
    int16_t nextangle_current;	// Next current orientation
    int16_t nextangle_target;	// Next current orientation
    int16_t nextangle_turn;	// Increase in current orientation when != nextagnle
    int8_t pathlength;
    int8_t pathmax;
};

#endif
