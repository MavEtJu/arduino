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
  static uint16_t c = 0;
  
    if (c++ == 0)
        loop1();
    loop2();
}

void loop1() {
    colorWipe2(strip.Color( 0, 16, 16), 25);
}

void loop2() {
    colorWipe3(strip.Color( 0, 16, 16), 25, 5);
    colorWipe3(strip.Color(16, 16,  0), 25, 7);
    colorWipe3(strip.Color(16,  0, 16), 25, 9);
}

// Fill the dots one after the other with a color
void colorWipe2(uint32_t c, uint8_t wait) {
  uint16_t i;
  uint32_t black = strip.Color(0, 0, 0);
  
  for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
      strip.setPixelColor(i, black);
  }
}

// Fill the dots one after the other with a color
void colorWipe3(uint32_t c, uint8_t wait, uint8_t size) {
  uint16_t i, j;
  uint32_t black = strip.Color(0, 0, 0);
  
  for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c >> 4);
      strip.setPixelColor(i + 1, c >> 2);
      for (j = 4; j < size; j++) {
          strip.setPixelColor(j, c);
      }
      strip.setPixelColor(i + size - 2, c >> 2);
      strip.setPixelColor(i + size - 1, c >> 4);
      strip.show();
      delay(wait);
      strip.setPixelColor(i, black);
  }
}
