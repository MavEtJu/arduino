#include <Adafruit_NeoPixel.h>

#define PIN_BLINK   13
#define PIN_STRIP    6

#define LAYERS          7
#define LEDSPERLAYER   20
#define DELAY          25

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN_STRIP, NEO_GRB + NEO_KHZ800);
uint32_t red = strip.Color(8, 0, 0);
uint32_t green = strip.Color(0, 8, 0);
uint32_t black = strip.Color(0, 0, 0);
uint32_t purple = strip.Color(8, 0, 8);



void
setup(void)
{
    pinMode(PIN_BLINK, OUTPUT);
    strip.begin();
    strip.show();
}


void
loop(void)
{
    loop_blink();
    loop_redgreenchasing();
    loop_tower();
    strip.show();
    delay(DELAY);
}


void
loop_blink(void)
{
    // Blink once every eight ticks.
    static byte onoff = 0;
    digitalWrite(PIN_BLINK, (++onoff % 8) == 0 ? HIGH : LOW);
}


#define TOWER_DELAY    3
void
loop_tower()
{
    static byte h = 0;
    static int h_delay = TOWER_DELAY;
    static int direction = 1;
    
    if (--h_delay == 0) {
        if (direction == 1) {
            if (++h == LAYERS - 1) {
                direction = -1;
            }
        } else {
            if (--h == 0) {
                direction = 1;
            }
        }        
        h_delay = TOWER_DELAY;
    }
    line(h, purple);
}

void
line(byte l, uint32_t colour)
{
    byte offset = l * LEDSPERLAYER;
    
    for (byte i = offset; i < offset + LEDSPERLAYER; i++) {
        strip.setPixelColor(i, colour);
    }
}


#define X_RED_DELAY    5
#define X_GREEN_DELAY  1
void
loop_redgreenchasing(void)
{
    byte i;
    static int x_red = 0, x_green = LEDSPERLAYER;
    static int x_red_delay = X_RED_DELAY;
    static int x_green_delay = X_GREEN_DELAY;
    
    // Make all black
    for (i = 0; i < LAYERS * LEDSPERLAYER; i++) {
        strip.setPixelColor(i, black);
    }
    
    // Red moves every five ticks.
    if (--x_red_delay == 0) {
        x_red++;
        x_red %= LEDSPERLAYER;
        x_red_delay = X_RED_DELAY;
    }
    
    // Green moves every tick.
    if (--x_green_delay == 0) {
        x_green--;
        if (x_green < 0)
            x_green = LEDSPERLAYER;
        x_green_delay = X_GREEN_DELAY;
    }
    
    for (i = 0; i < LAYERS; i++) {
        strip.setPixelColor(i * LEDSPERLAYER + x_red, red);
    }
    for (i = 0; i < LAYERS; i++) {
        strip.setPixelColor(i * LEDSPERLAYER + x_green, green);
    }
}
