//#define MEMORY
//#define SERIAL

#include <Arduino.h>
#ifdef SIMULATOR
#include <time.h>
#endif
#ifdef MEMORY
#include <MemoryFree.h>
#endif
#include "LED_Strip.h"
#include "StringEncode.h"
#include "LED_Animation.h"
#include "LED_Text.h"
#include "A_Tools.h"
#include "slides.h"
#include "animations.h"

#define PIN_BLINK   13
#define PIN_STRIP    6

#define VIEW_WIDTH  16
#define VIEW_HEIGHT 16


LED_Strip led = LED_Strip(VIEW_WIDTH * VIEW_HEIGHT, PIN_STRIP);

void
loop_blink(void)
{
    // Blink once every eight ticks.
    static byte onoff = 0;
    digitalWrite(PIN_BLINK, (++onoff % 8) == 0 ? HIGH : LOW);
}


void
setup(void)
{
#ifdef SIMULATOR
    srandom(time(NULL));
#else
    randomSeed(analogRead(0));
#endif
#ifdef SERIAL
    Serial.begin(9600);
    Serial.println(F("Hello, world!"));
# ifdef MEMORY
#  ifndef SIMULATOR
    Serial.print(F("free1: "));
    Serial.println(freeMemory());
#  endif
# endif
#endif
    pinMode(PIN_BLINK, OUTPUT);
#ifdef SIMULATOR
    led.view(VIEW_WIDTH, VIEW_HEIGHT, 0);
#else
    led.view(VIEW_WIDTH, VIEW_HEIGHT, VIEW_SQUARE);
#endif
    led.start();
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
    Serial.print(F("free2: "));
    Serial.println(freeMemory());
#  endif
# endif
#endif
}

LED_Animation *animation[1] = {NULL};
LED_Slideshow *slideshow[1] = {NULL};

void
loop(void)
{
    loop_blink();
    led.clear();

    static int16_t phasenr = 0;
    static unsigned long started = 0;

    /* testing */
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
    FREEMEMORY(F("loop"));
#  endif
# endif
#endif

//#define TESTING
#ifdef TESTING
    static LED_cross1 *p = new LED_cross1(&led, VIEW_WIDTH, VIEW_HEIGHT);
    //static LED_quickbrowfox1 *p = new LED_quickbrowfox1(&led, VIEW_WIDTH, VIEW_HEIGHT);
    p->loop();
    led.display();
    started++;
# ifdef SERIAL
//    Serial.println(started);
# endif
    return;
#endif

    if (started == 0 || started + 5l * 1000l < millis()) {
#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory before free: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif
        if (animation[0] != NULL) {
            animation[0]->destroy();
            delete(animation[0]);
            animation[0] = NULL;
        }
        if (slideshow[0] != NULL) {
            slideshow[0]->destroy();
            delete(slideshow[0]);
            slideshow[0] = NULL;
        }

#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory after free: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif

	int phase = 0;
	slideshow[0] = NULL;
	animation[0] = NULL;
	#define NEW_ANIMATION(__t)  \
		if (phase++ == phasenr) { \
		    __t *p = new __t(&led, VIEW_WIDTH, VIEW_HEIGHT); \
		    animation[0] = p; \
		} else
	#define NEW_SLIDESHOW(__t)  \
		if (phase++ == phasenr) { \
		    __t *p = new __t(&led, VIEW_WIDTH, VIEW_HEIGHT); \
		    slideshow[0] = p; \
		} else

#ifdef SERIAL
	Serial.print(F("phasenr: "));
	Serial.println(phasenr);
#endif
	NEW_ANIMATION(LED_led00_blink1)
	NEW_ANIMATION(LED_quickbrowfox1)
	NEW_ANIMATION(LED_spaceinvaders1)
	NEW_ANIMATION(LED_sinus1)
	NEW_ANIMATION(LED_lines1)
	NEW_ANIMATION(LED_sinus2)
	NEW_ANIMATION(LED_lineshorver1)
	NEW_ANIMATION(LED_squares1)
	NEW_ANIMATION(LED_torch1)
	NEW_SLIDESHOW(LED_mario1)
	NEW_SLIDESHOW(LED_galaga1)
	NEW_ANIMATION(LED_torch2)
	NEW_SLIDESHOW(LED_minecraft1)
	NEW_ANIMATION(LED_cross1)
	{ 
	    LED_led00_blink1 *p = new LED_led00_blink1(&led, VIEW_WIDTH, VIEW_HEIGHT);
	    animation[0] = p;
	    phasenr = -1;
	    started = 0;
#ifdef SERIAL
	    Serial.println(F("Reset"));
#endif
	}
	phasenr++;

#ifdef SERIAL
# ifdef MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory after new: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif
        started = millis();
    }
    if (animation[0] != NULL)
        animation[0]->loop();
    if (slideshow[0] != NULL)
        slideshow[0]->loop();

    led.display();
}