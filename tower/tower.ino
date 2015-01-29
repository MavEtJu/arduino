#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    uint32_t red = strip.Color(8, 0, 0);
    uint32_t black = strip.Color(0, 0, 0);
    uint8_t DELAY = 25;
    
    for (byte l = 0; l < 7; l++) {
        line(l, red);
        strip.show();
        delay(DELAY);
        line(l, black);
    }
    
    for (byte i = 7; i > 0; i--) {
        line(6, strip.Color(i, 0, 0));
        strip.show();
        delay(4 * DELAY);
    }
    for (byte i = 0; i < 8; i++) {
        line(6, strip.Color(i, 0, 0));
        strip.show();
        delay(4 * DELAY);
    }
    line(6, black);

    for (byte l = 5; l > 0; l--) {
        line(l, red);
        strip.show();
        delay(DELAY);
        line(l, black);
    }
}

#define LEDPERLINE 20
void line(byte l, uint32_t color) {
    byte offset = l * LEDPERLINE;
    
    for (byte i = offset; i < offset + LEDPERLINE; i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
    delay(25);
}


