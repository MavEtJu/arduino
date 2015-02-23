
#ifndef LED_Animation__h
#define LED_Animation__h

// ==============================
class LED_Animation {
public:
    LED_Animation(void);
    virtual ~LED_Animation(void);
    virtual void destroy(void);
    void loop(void);
    virtual void animation(void);
    uint16_t step;
    uint8_t delayms;
};

#endif
