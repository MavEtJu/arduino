//
//

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef SIMULATOR
#include <time.h>
#endif
#include "LED_Strip.h"

LED_Strip::LED_Strip(uint16_t amount, uint8_t pin) : Adafruit_NeoPixel(amount, pin, NEO_GRB + NEO_KHZ800)
{
    _colourlast = Color(0, 0, 0);
    colour_red = Color(8, 0, 0);
    colour_green = Color(0, 8, 0);
    colour_blue = Color(0, 0, 8);
    colour_black = Color(0, 0, 0);
    colour_white = Color(8, 8, 8);
    colour_magenta = Color(8, 0, 8);
    colour_cyan = Color(0, 8, 8);
    colour_yellow = Color(8, 8, 0);
    _strip = (LED *)pixels;
    _matrix = NULL;
    _ymax = 0;
    _xmax = 0;
    _options = 0;
 //   letters_init();
#ifdef SIMULATOR
    srandom(time(NULL));
#else
    randomSeed(analogRead(0));
#endif
}

LED
LED_Strip::Color(uint8_t r, uint8_t g, uint8_t b)
{
    LED l;
    l.red = r;
    l.green = g;
    l.blue = b;
    return l;
}

void
LED_Strip::start(void)
{
    this->begin();
    this->show();
}

// Set the size of the view
void
LED_Strip::view(uint16_t xmax, uint16_t ymax, uint8_t options)
{
    _xmax = xmax;
    _ymax = ymax;
    _matrix = (LED **)malloc(sizeof(LED *) * ymax);
    for (uint16_t y = 0; y < _ymax; y++) {
        _matrix[y] = _strip + y * _xmax;
    }
    _options = options;

    #ifdef SIMULATOR
    setsize(xmax, ymax);
    #endif
}

// Display the drawn objects to the LED strip
void
LED_Strip::display(void)
{
    if ((_options & VIEW_SQUARE) != 0) {
        // Even lines go RTL, odd lines go LTR
        for (uint8_t y = 0; y < _ymax; y++) {
            if (y % 2 == 0)
                continue;
            LED l;
            LED *line = _matrix[y];
            for (uint8_t x = 0; x < _xmax / 2; x++) {
                l = line[x];
                line[x] = line[_xmax - 1 - x];
                line[_xmax - 1 - x] = l;
            }
        }
    }
    show();
}

// Clear everything
void
LED_Strip::clear(void)
{
    clear(colour_black);
}

void
LED_Strip::clear(LED colour)
{
    for (uint16_t x = 0; x < _xmax * _ymax; x++) {
        _strip[x] = colour_black;
    }
}


// Set the current colour
void
LED_Strip::colour_set(LED colour)
{
    _colourlast = colour;
}

LED
LED_Strip::colour_get(void)
{
    return _colourlast;
}

LED
LED_Strip::colour_random(void)
{
    switch (rand() % 8) {
        case 0: return colour_white;
        case 1: return colour_black;
        case 2: return colour_red;
        case 3: return colour_green;
        case 4: return colour_blue;
        case 5: return colour_cyan;
        case 6: return colour_magenta;
        case 7: return colour_yellow;
        default:
            return colour_white;
    }
}


// Colour the LEDs in the strip from offset 1 to offset 2
void
LED_Strip::strip_o1_o2(uint16_t o1, uint16_t o2)
{
    for (uint16_t o = o1; o <= o2; o++) {
        _strip[o] = _colourlast;
    }
}
void
LED_Strip::strip_o1_o2(uint16_t o1, uint16_t o2, LED colour)
{
    _colourlast = colour;
    strip_o1_o2(o1, o2);
}

// Colour the LEDs in the strip from offset to offset + length
void
LED_Strip::strip_o_length(uint16_t o, uint16_t length)
{
    for (uint16_t x = o; x < o + length; x++) {
        _strip[x] = _colourlast;
    }
}
void
LED_Strip::strip_o_length(uint16_t o, uint16_t length, LED colour)
{
    _colourlast = colour;
    strip_o_length(o, length);
}

// Plot a dot
void
LED_Strip::dot(int16_t x, int16_t y)
{
    if (x < 0 || x >= _xmax)
        return;
    if (y < 0 || y >= _ymax)
        return;
    _matrix[y][x] = _colourlast;
}

void
LED_Strip::dot(int16_t x, int16_t y, LED colour)
{
    _colourlast = colour;
    dot(x, y);
}

// Colour the LEDs in the matrix from (x1, y1) x (x2, y2)
void
LED_Strip::square(int16_t xo, int16_t yo, uint16_t dx, uint16_t dy)
{
    for (int16_t x = 0; x < dx; x++) {
        if (xo + x < 0 || xo + x >= _xmax)
            continue;
        for (int16_t y = 0; y < dy; y++) {
            if (yo + y < 0 || yo + y >= _ymax)
                continue;
            _matrix[yo + y][xo + x] = _colourlast;
        }
    }
}

void
LED_Strip::square(int16_t xo, int16_t yo, uint16_t dx, uint16_t dy, LED colour)
{
    _colourlast = colour;
    square(xo, yo, dx, dy);
}

// Draw a line
// http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm_for_integer_arithmetic
// http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
void
LED_Strip::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    int w = x2 - x1;
    int h = y2 - y1;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if (w < 0)
        dx1 = -1;
    else if (w > 0)
            dx1 = 1;
    if (h < 0)
        dy1 = -1;
    else if (h > 0)
        dy1 = 1;
    if (w < 0)
        dx2 = -1;
    else if (w > 0)
        dx2 = 1;
        
    int longest = abs(w);
    int shortest = abs(h);
    if (!(longest > shortest)) {
        longest = abs(h);
        shortest = abs(w);
        if (h < 0)
            dy2 = -1;
        else if (h > 0)
            dy2 = 1;
        dx2 = 0;
    }
    
    int numerator = longest >> 1;
    for (int i = 0; i <= longest; i++) {
        dot(x1, y1);
        numerator += shortest;
        if (!(numerator < longest)) {
            numerator -= longest;
            x1 += dx1;
            y1 += dy1;
        } else {
            x1 += dx2;
            y1 += dy2;
        }
    }
}

void
LED_Strip::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, LED colour)
{
    _colourlast = colour;
    line(x1, y1, x2, y2);
}

void
LED_Strip::line(struct coordinates c1, struct coordinates c2)
{
    line(c1.x, c1.y, c2.x, c2.y);
}

void
LED_Strip::line(struct coordinates c1, struct coordinates c2, LED colour)
{
    line(c1.x, c1.y, c2.x, c2.y, colour);
}

void
LED_Strip::horline(int16_t y, int16_t x1, int16_t x2)
{
    for (int16_t x = x1; x <= x2; x++) {
	dot(x, y);
    }
}

void
LED_Strip::horline(int16_t y, int16_t x1, int16_t x2, LED colour)
{
    _colourlast = colour;
    this->horline(y, x1, x2);
}

void
LED_Strip::verline(int16_t x, int16_t y1, int16_t y2)
{
    for (int16_t y = y1; y <= y2; y++) {
	dot(x, y);
    }
}

void
LED_Strip::verline(int16_t x, int16_t y1, int16_t y2, LED colour)
{
    _colourlast = colour;
    this->verline(x, y1, y2);
}


// Copy the blob into the matrix
void
LED_Strip::blob(int16_t xo, int16_t yo, int16_t dx, int16_t dy, LED *colour)
{
    for (int16_t y = 0; y < dy; y++) {
        for (int16_t x = 0; x < dx; x++) {
            dot(xo + x, yo + dy - y, colour[dx * dy - (y * dx + x)]);
        }
    }
}

void
LED_Strip::blob(int16_t xo, int16_t yo, int16_t dx, int16_t dy, const char *s, LED colour)
{
    for (int16_t y = 0; y < dy; y++) {
        for (int16_t x = 0; x < dx; x++) {
            LED c = colour_black;
            if (s[y * dx + x] != ' ')
                c = colour;
            dot(xo + x, yo + dy - y, c);
        }
    }
}