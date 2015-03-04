#ifndef animations__h
#define animations__h

#define SIMPLECONSTRUCTOR(__t__) __t__(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT) {};

class LED_led00_blink1 : public LED_Animation {
    public:
    SIMPLECONSTRUCTOR(LED_led00_blink1);
    void animation(void);
};

class LED_quickbrowfox1 : public LED_Animation {
    public:
    LED_quickbrowfox1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    ~LED_quickbrowfox1(void);
    void animation(void);
    LED_Text *text;
};

class LED_lineshorver1 : public LED_Animation {
    public:
    SIMPLECONSTRUCTOR(LED_lineshorver1);
    void animation(void);
};

#define LED_lines1_history  5
class LED_lines1 : public LED_Animation {
    public:
    LED_lines1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);
    void shift_history(void);
    LED c[LED_lines1_history];
    char dir;
    uint16_t x1, x2, y1, y2;
    int16_t dx1, dx2, dy1, dy2;
    uint16_t x1_final, x2_final, y1_final, y2_final;

    uint16_t x1s[LED_lines1_history], x2s[LED_lines1_history], y1s[LED_lines1_history], y2s[LED_lines1_history];
};

class LED_squares1 : public LED_Animation {
public:
    LED_squares1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);
    LED c;
};

#define LED_squares2_history 20
class LED_squares2 : public LED_Animation {
public:
    LED_squares2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);
    struct area a[LED_squares2_history];
    LED c[LED_squares2_history], c_last;
    void shift_history(struct area a, LED c);
};

#define LED_movingsquares1_squares 4
class LED_movingsquares1 : public LED_Animation {
public:
    LED_movingsquares1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);
    LED c[LED_movingsquares1_squares];
    int16_t x0[LED_movingsquares1_squares], y0[LED_movingsquares1_squares], x1[LED_movingsquares1_squares],
        y1[LED_movingsquares1_squares], dx[LED_movingsquares1_squares], dy[LED_movingsquares1_squares],
        size[LED_movingsquares1_squares], x[LED_movingsquares1_squares], y[LED_movingsquares1_squares];
};

class LED_cross1 : public LED_Animation {
    public:
    LED_cross1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);
    
    #define LED_cross1_history  5
    LED c[LED_cross1_history];
    struct coordinates c1[LED_cross1_history], c2[LED_cross1_history];
};

class LED_sinus1 : public LED_Animation {
    public:
    LED_sinus1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);
};

class LED_sinus2 : public LED_Animation {
    public:
    LED_sinus2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void animation(void);

    int8_t height;
    int8_t direction;
};

#define LED_spaceinvaders_IMGS 11
class LED_spaceinvaders1 : public LED_Animation {
    public:
    LED_spaceinvaders1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    void destroy(void);
    void animation(void);

    StringEncodePlain *enc;
    const char **imgs;
    char img[128];
    uint16_t imglen;
    uint16_t x;
    uint8_t imgnr;
    LED colours[LED_spaceinvaders_IMGS];
    uint8_t width[LED_spaceinvaders_IMGS];
    uint8_t encbits[LED_spaceinvaders_IMGS];
};

struct coal {
	int16_t x, y;
        int16_t intensity;
};

class LED_torch1 : public LED_Animation {
    public:
    LED_torch1(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    ~LED_torch1(void);
    void animation(void);
    
    LED colour_floor;
    int numcoals;
    struct coal *coals;
};

class LED_torch2 : public LED_Animation {
public:
    LED_torch2(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT);
    ~LED_torch2(void);
    
    void animation(void);
    int numcoals;
    struct coal *coals;
};

#endif
