#include <Arduino.h>
#ifdef SIMULATOR
#include <time.h>
#endif
#ifdef DEBUG_MEMORY
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

#ifndef DELAY
#define DELAY	30l
#endif

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
# ifdef DEBUG_MEMORY
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
# ifdef DEBUG_MEMORY
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
# ifdef DEBUG_MEMORY
#  ifndef SIMULATOR
    //FREEMEMORY(F("loop"));
#  endif
# endif
#endif

//#define TESTING
#ifdef TESTING
    #define TEST(__t__) \
	static __t__ *p = new __t__(&led, VIEW_WIDTH, VIEW_HEIGHT);

    //TEST(LED_cross1)
    //TEST(LED_lines1)
    //TEST(LED_lines2)
    //TEST(LED_movingsquares1)
    //TEST(LED_movingsquares2)
    //TEST(LED_plasma1)
    //TEST(LED_sinus1)
    //TEST(LED_sinus2)
    //TEST(LED_sinus3)
    //TEST(LED_spaceinvaders1)
    //TEST(LED_spinningsquares1)
    //TEST(LED_square_splitting)
    //TEST(LED_squares1)
    //TEST(LED_squares2)
    //TEST(LED_squares3)
    //TEST(LED_squares4)
    //TEST(LED_test)
    //TEST(LED_torch1)
    //TEST(LED_torch2)

    p->loop();
    led.display();
    started++;
# ifdef SERIAL
//    Serial.println(started);
# endif
    return;
#endif

    if ((animation[0] == NULL && slideshow[0] == NULL) || (started == 0) || (started + DELAY * 1000l < millis())) {
#ifdef SERIAL
# ifdef DEBUG_MEMORY
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
# ifdef DEBUG_MEMORY
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
   	// NEW_ANIMATION(LED_led00_blink1)
	NEW_ANIMATION(LED_test)
	// NEW_ANIMATION(LED_quickbrowfox1)
	NEW_ANIMATION(LED_torch2)
	NEW_ANIMATION(LED_torch1)
	NEW_ANIMATION(LED_spinningsquares1)
	//NEW_SLIDESHOW(LED_galaga1)
	NEW_ANIMATION(LED_spaceinvaders1)
	NEW_ANIMATION(LED_plasma1)
	NEW_ANIMATION(LED_movingsquares1)
	NEW_ANIMATION(LED_sinus1)
	NEW_ANIMATION(LED_square_splitting)
	NEW_ANIMATION(LED_lines1)
	NEW_ANIMATION(LED_movingsquares2)
	NEW_ANIMATION(LED_sinus2)
	//NEW_ANIMATION(LED_lineshorver1)
	NEW_ANIMATION(LED_squares1)
	NEW_ANIMATION(LED_lines2)
	NEW_ANIMATION(LED_sinus3)
	//NEW_SLIDESHOW(LED_mario1)
	NEW_ANIMATION(LED_squares2)
	NEW_ANIMATION(LED_squares3)
	//NEW_SLIDESHOW(LED_minecraft1)
	NEW_ANIMATION(LED_cross1)
	NEW_ANIMATION(LED_squares4)
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

	if (animation[0] != NULL && animation[0]->broken) {
	    Serial.println(F("Animation broken before loop()"));
	    delete(animation[0]);
	    animation[0] = NULL;
	}
	if (slideshow[0] != NULL && slideshow[0]->broken) {
	    Serial.println(F("Slideshow broken before loop()"));
	    delete(slideshow[0]);
	    slideshow[0] = NULL;
	}


#ifdef SERIAL
# ifdef DEBUG_MEMORY
#  ifndef SIMULATOR
        Serial.print(F("Free Memory after new: "));
        Serial.println(freeMemory());
#  endif
# endif
#endif
        started = millis();
    }
    if (animation[0] != NULL) {
        animation[0]->loop();
	if (animation[0]->broken) {
	    Serial.println(F("Animation broken after loop()"));
	    delete(animation[0]);
	    animation[0] = NULL;
	}
    }
    if (slideshow[0] != NULL) {
        slideshow[0]->loop();
	if (slideshow[0]->broken) {
	    Serial.println(F("Slideshow broken after loop()"));
	    delete(slideshow[0]);
	    slideshow[0] = NULL;
	}
    }

    led.display();
}
