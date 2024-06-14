/*
  Fire-staff
  by Edwin Groothuis
 */


#include <Arduino.h>
#include "../libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h"

#define NEOPIN	3	// D3
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, NEOPIN, NEO_GRB + NEO_KHZ800);

uint32_t black = strip.Color( 0, 0, 0);
int wait = 100;
int loopcounter = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	strip.begin();
	strip.show();

}

// the loop function runs over and over again forever
void loop() {
	unsigned int i;
	uint32_t c;
	int v = 2; //* random();
	switch (++loopcounter % 8) {
	case 0:
		c = strip.Color(v, 0, 0);
		break;
	case 1:
		c = strip.Color(0, v, 0);
		break;
	case 2:
		c = strip.Color(0, 0, v);
		break;
	case 3:
		c = strip.Color(v, v, 0);
		break;
	case 4:
		c = strip.Color(0, v, v);
		break;
	case 5:
		c = strip.Color(v, 0, v);
		break;
	case 6:
		c = strip.Color(v, v, v);
		break;
	case 7:
		c = strip.Color(0, 0, 0);
		break;
	}

	for (i = 0; i < strip.numPixels(); i++) {
		Serial.println(i);
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
		strip.setPixelColor(i, black);
	}
}
