//
//

#if !defined led_tools__h
#define led_tools__h

#include <Adafruit_NeoPixel.h>

class LED : public Adafruit_NeoPixel {
    public:
    LED(uint16_t amount, uint8_t pin);
    void start(void);
    
    // Set the current colour
    void colour_set(uint32_t colour);
    
    // Colour the LEDs from offset 1 to offset 2
    void colour_o1_o2(uint16_t o1, uint16_t o2);
    void colour_o1_o2(uint16_t o1, uint16_t o2, uint32_t colour);
    
    // Colour the LEDs from offset to offset + length
    void colour_o_length(uint16_t o, uint16_t length);
    void colour_o_length(uint16_t o, uint16_t length, uint32_t colour);

    private:
    uint32_t _colourlast;
};

#endif
