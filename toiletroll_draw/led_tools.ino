//
//

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "led_tools.h"

LED::LED(uint16_t amount, uint8_t pin) : Adafruit_NeoPixel(amount, pin, NEO_GRB + NEO_KHZ800)
{
    _colourlast = this->Color(0, 0, 0);
    colour_red = Color(8, 0, 0);
    colour_green = Color(0, 8, 0);
    colour_blue = Color(0, 0, 8);
    colour_black = Color(0, 0, 0);
    _strip = (uint32_t *)malloc(amount * sizeof(uint32_t));
}    

void
LED::start(void)
{
    this->begin();
    this->show();
}

// Set the size of the view
void
LED::view(uint16_t xmax, uint16_t ymax)
{
    _xmax = xmax;
    _ymax = ymax;
    _matrix = (uint32_t **)malloc(sizeof(uint32_t *) * ymax);
    for (uint16_t y = 0; y < _ymax; y++) {
        _matrix[y] = _strip + y * _xmax;
    }
}

// 
void
LED::display(void)
{
    for (uint16_t o = 0; o < _xmax * _ymax; o++) {
        setPixelColor(o, _strip[o]);
    }
    show();
}

// Clear everything
void
LED::clear(void)
{
    clear(led.colour_black);
}

void
LED::clear(uint32_t colour)
{
    for (uint16_t x = 0; x < _xmax * _ymax; x++) {
        _strip[x] = colour;
    }
}


// Set the current colour
void
LED::colour_set(uint32_t colour)
{
    _colourlast = colour;
}

// Colour the LEDs in the strip from offset 1 to offset 2
void
LED::strip_o1_o2(uint16_t o1, uint16_t o2)
{
    for (uint16_t o = o1; o <= o2; o++) {
        _strip[o] = _colourlast;
    }
}
void
LED::strip_o1_o2(uint16_t o1, uint16_t o2, uint32_t colour)
{
    _colourlast = colour;
    strip_o1_o2(o1, o2);
}

// Colour the LEDs in the strip from offset to offset + length
void
LED::strip_o_length(uint16_t o, uint16_t length)
{
    for (uint16_t x = o; x < o + length; x++) {
        _strip[x] = _colourlast;
    }
}
void
LED::strip_o_length(uint16_t o, uint16_t length, uint32_t colour)
{
    _colourlast = colour;
    strip_o_length(o, length);
}

// Colour the LEDs in the matrix from (x1, y1) x (x2, y2)
void
LED::square(int16_t xo, int16_t yo, uint16_t dx, uint16_t dy)
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
LED::square(int16_t xo, int16_t yo, uint16_t dx, uint16_t dy, uint32_t colour)
{
    _colourlast = colour;
    square(xo, yo, dx, dy);
}


