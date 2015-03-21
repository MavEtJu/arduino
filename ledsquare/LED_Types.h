#ifndef LED_Types__h
#define LED_Types__h

struct LED {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
};
typedef struct LED LED;

struct coordinates {
    int16_t x, y;
};
struct distance {
    int16_t dx, dy;
};
struct area {
    struct coordinates c1, c2;
};

#endif
