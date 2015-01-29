//
//

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "led_tools.h"

LED::LED(uint16_t amount, uint8_t pin) : Adafruit_NeoPixel(amount, pin, NEO_GRB + NEO_KHZ800)
{
    _colourlast = this->Color(0, 0, 0);
}    

void
LED::start(void)
{
    this->begin();
    this->show();
}

// Set the current colour
void
LED::colour_set(uint32_t colour)
{
    _colourlast = colour;
}

// Colour the LEDs from offset 1 to offset 2
void
LED::colour_o1_o2(uint16_t o1, uint16_t o2)
{
    this->colour_o1_o2(o1, o2, _colourlast);
}
void
LED::colour_o1_o2(uint16_t o1, uint16_t o2, uint32_t colour)
{
    _colourlast = colour;
    for (uint16_t o = o1; o <= o2; o++) {
        this->setPixelColor(o, colour);
    }
}

// Colour the LEDs from offset to offset + length
void
LED::colour_o_length(uint16_t o, uint16_t length)
{
    this->colour_o_length(o, length, _colourlast);
}
void
LED::colour_o_length(uint16_t o, uint16_t length, uint32_t colour)
{
    _colourlast = colour;
    for (uint16_t x = o; x < o + length; x++) {
        this->setPixelColor(x, colour);
    }
}

