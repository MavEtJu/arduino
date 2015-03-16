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

#endif
