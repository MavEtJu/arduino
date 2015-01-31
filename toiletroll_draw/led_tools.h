//
//

#if !defined led_tools__h
#define led_tools__h

#include <Adafruit_NeoPixel.h>

class LED : public Adafruit_NeoPixel {
    public:
    LED(uint16_t amount, uint8_t pin);
    void start(void);
    
    // Set the size of the view
    void view(uint16_t xmax, uint16_t ymax);
    
    // Display the current view
    void display(void);
    
    // Clear everything
    void clear(void);
    void clear(uint32_t colour);
    
    // Set the current colour
    void colour_set(uint32_t colour);
    
    // Colour the LEDs in the strip from offset 1 to offset 2
    void strip_o1_o2(uint16_t o1, uint16_t o2);
    void strip_o1_o2(uint16_t o1, uint16_t o2, uint32_t colour);
    
    // Colour the LEDs in the strip from offset to offset + length
    void strip_o_length(uint16_t o, uint16_t length);
    void strip_o_length(uint16_t o, uint16_t length, uint32_t colour);
    
    // Colour the LED in the matrix in the dot of (x, y)
    void dot(int16_t x, int16_t y);
    void dot(int16_t x, int16_t y, uint32_t colour);
    
    // Colour the LEDs in the matrix in the square from (x, y) x (x + dx, y + dy)
    void square(int16_t x, int16_t y, uint16_t dx, uint16_t dy);
    void square(int16_t x, int16_t y, uint16_t dx, uint16_t dy, uint32_t colour);
    
    // Colour the LEDs in the matrix in a line from (x1, y1) to (x2, y2)
    void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t colour);
    
    // Draw a character
    void text(int16_t x, int16_t y, char *text);
    void text(int16_t x, int16_t y, char *text, uint32_t colour);
    uint16_t text_width(char *text);

    // Predefined colours
    uint32_t colour_red, colour_green, colour_blue;
    uint32_t colour_purple, colour_cyan, colour_yellow;
    uint32_t colour_white, colour_black;
    uint32_t colour_random(void);

    private:
    uint32_t **_matrix;
    uint32_t *_strip;
    uint32_t _colourlast;
    uint16_t _xmax, _ymax;
    char **letters;
    void letters_init(void);

    
};

#endif
