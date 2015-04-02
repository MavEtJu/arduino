//
//

#ifndef LED_Strip__h
#define LED_Strip__h

#include <Adafruit_NeoPixel.h>

#define VIEW_SQUARE  1

#include "LED_Types.h"

class LED_Strip : public Adafruit_NeoPixel {
public:
    LED_Strip(uint16_t amount, uint8_t pin);
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
    LED colour_get(void);
    LED colour_fade(LED colour, int fade);
    LED colour_fade_seq(LED colour, int fade);
    int colour_same(LED c1, LED c2);
    int colour_same3(LED c1, LED c2, LED c3);
    int colour_same4(LED c1, LED c2, LED c3, LED c4);
    LED colour_transform(LED c1, LED c2, int steps, int step);
    LED colour_transform(int step);
    
    // Colour the LEDs in the strip from offset 1 to offset 2
    void strip_o1_o2(uint16_t o1, uint16_t o2);
    void strip_o1_o2(uint16_t o1, uint16_t o2, LED colour);
    
    // Colour the LEDs in the strip from offset to offset + length
    void strip_o_length(uint16_t o, uint16_t length);
    void strip_o_length(uint16_t o, uint16_t length, LED colour);
    
    // Colour the LED in the matrix in the dot of (x, y)
    void dot(int16_t x, int16_t y);
    void dot(int16_t x, int16_t y, LED colour);
    void dot(struct coordinates c);
    void dot(struct coordinates c, LED colour);
    
    // Colour the LEDs in the matrix in the square from (x, y) x (x + dx, y + dy)
    void square(int16_t x, int16_t y, int16_t dx, int16_t dy);
    void square(int16_t x, int16_t y, int16_t dx, int16_t dy, LED colour);
    void square(struct coordinates c, struct distance d);
    void square(struct coordinates c, struct distance d, LED colour);
    void square(struct area a);
    void square(struct area a, LED colour);
    
    // Colour the LEDs in the matrix in a line from (x1, y1) to (x2, y2)
    void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, LED colour);
    void line(struct coordinates c1, struct coordinates c2);
    void line(struct coordinates c1, struct coordinates c2, LED colour);
    void horline(int16_t y, int16_t x1, int16_t x2);
    void horline(int16_t y, int16_t x1, int16_t x2, LED colour);
    void verline(int16_t x, int16_t y1, int16_t y2);
    void verline(int16_t x, int16_t y1, int16_t y2, LED colour);
    
    // Copy the blob into the matrix
    void blob(int16_t xo, int16_t yo, int16_t dx, int16_t dy, LED *colour);
    void blob(int16_t xo, int16_t yo, int16_t dx, int16_t dy, const char *s, LED colour);
    
    // Predefined colours
    LED colour_red, colour_green, colour_blue;
    LED colour_magenta, colour_cyan, colour_yellow;
    LED colour_white, colour_black;
    LED colour_random(void);
    LED colour_random_notblack(void);

    private:
    LED **_matrix;
    LED *_strip;
    LED _colourlast;
    LED *_colourtransform;
    int16_t _xmax, _ymax;
    uint8_t _options;
};

#endif
