//
//

#if !defined led_tools__h
#define led_tools__h

#include <Adafruit_NeoPixel.h>

#define VIEW_SQUARE  1

struct LED {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
};
typedef struct LED LED;

class LEDstrip : public Adafruit_NeoPixel {
    public:
    LEDstrip(uint16_t amount, uint8_t pin);
    void start(void);
    
    // Set the size of the view
    void view(uint16_t xmax, uint16_t ymax, uint8_t options);
    
    // Display the current view
    void display(void);
    LED Color(uint8_t r, uint8_t g, uint8_t b);
    
    // Clear everything
    void clear(void);
    void clear(LED colour);
    
    // Set the current colour
    void colour_set(LED colour);
    
    // Colour the LEDs in the strip from offset 1 to offset 2
    void strip_o1_o2(uint16_t o1, uint16_t o2);
    void strip_o1_o2(uint16_t o1, uint16_t o2, LED colour);
    
    // Colour the LEDs in the strip from offset to offset + length
    void strip_o_length(uint16_t o, uint16_t length);
    void strip_o_length(uint16_t o, uint16_t length, LED colour);
    
    // Colour the LED in the matrix in the dot of (x, y)
    void dot(int16_t x, int16_t y);
    void dot(int16_t x, int16_t y, LED colour);
    
    // Colour the LEDs in the matrix in the square from (x, y) x (x + dx, y + dy)
    void square(int16_t x, int16_t y, uint16_t dx, uint16_t dy);
    void square(int16_t x, int16_t y, uint16_t dx, uint16_t dy, LED colour);
    
    // Colour the LEDs in the matrix in a line from (x1, y1) to (x2, y2)
    void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, LED colour);
    
    // Copy the blob into the matrix
    void blob(int16_t xo, int16_t yo, int16_t dx, int16_t dy, LED *colour);
    void blob(int16_t xo, int16_t yo, int16_t dx, int16_t dy, const char *s, LED colour);
    
    // Draw a character
    void text(int16_t x, int16_t y, const char *text);
    void text(int16_t x, int16_t y, const char *text, LED colour);
    uint16_t text_width(const char *text);

    // Predefined colours
    LED colour_red, colour_green, colour_blue;
    LED colour_magenta, colour_cyan, colour_yellow;
    LED colour_white, colour_black;
    LED colour_random(void);

    private:
    LED **_matrix;
    LED *_strip;
    LED _colourlast;
    uint16_t _xmax, _ymax;
    uint8_t _options;
    const char **letters;
    void letters_init(void);

    
};

#endif
