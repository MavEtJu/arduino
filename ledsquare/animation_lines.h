#ifndef animation_lines__h
#define animation_lines__h

#include "animation_lines.h"

class LED_lineshorver1 : public LED_Animation {
public:
    PARENTCONSTRUCTOR(LED_lineshorver1);
    void animation(void);
};

#define LED_lines1_history  5
class LED_lines1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_lines1);
    void animation(void);
    void shift_history(void);
    LED c[LED_lines1_history];
    char dir;
    uint16_t x1, x2, y1, y2;
    int16_t dx1, dx2, dy1, dy2;
    uint16_t x1_final, x2_final, y1_final, y2_final;

    uint16_t x1s[LED_lines1_history], x2s[LED_lines1_history], y1s[LED_lines1_history], y2s[LED_lines1_history];
};

class LED_cross1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_cross1);
    void animation(void);
    
    #define LED_cross1_history  5
    LED c[LED_cross1_history];
    struct coordinates c1[LED_cross1_history], c2[LED_cross1_history];
};

#define LED_lines2_history 4
struct LED_lines2_coordinates {
     struct coordinates c;
     int16_t a0, a1;
};
class LED_lines2 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_lines2);
    void animation(void);
    void shift_history(int16_t c1x, int16_t c1y, int16_t c2x, int16_t c2y);

    struct LED_lines2_coordinates *c;

    struct area history[LED_lines2_history];
    struct LED colour;

    int16_t x0, y0, coor;
    int16_t angle, length;
    int8_t ics;
};

class LED_lines3 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_lines3);
    void animation(void);
    LED c[2];
    int8_t stripes;
};

class LED_lines_waver1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_lines_waver1);
    void animation(void);
    #define LED_lines_waver1_origins	5
    struct coordinates origins[LED_lines_waver1_origins];
    int angle;
    int len;
    int number;
};

#endif
