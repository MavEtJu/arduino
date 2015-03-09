
//
//

#ifndef A_Tools__h
#define A_Tools__h

#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

/* https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory */
int freeRam(void);

#define FREERAM(f) \
    Serial.print(F(f)); \
    Serial.print(F(": FreeRam(): ")); \
    Serial.println(freeRam()); 

#define FREEMEMORY(T) \
    Serial.print(F(T)); \
    Serial.print(F(": freeMemory(): ")); \
    Serial.println(freeMemory());

#define PARENTCONSTRUCTOR(__t__) \
	__t__(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : \
	    LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT) {}
#define MYOWNCONSTRUCTOR(__t__) \
	__t__(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT)

#define MYCONSTRUCTOR_ANIMATION(__t__) \
	__t__::__t__(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Animation(led, VIEW_WIDTH, VIEW_HEIGHT)
#define MYCONSTRUCTOR_SLIDESHOW(__t__) \
	__t__::__t__(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT) : LED_Slideshow(led, VIEW_WIDTH, VIEW_HEIGHT)


#define SERIAL1(__a0__) \
	Serial.println(__a0__)
#define SERIAL2(__a1__, __a0__) \
	Serial.print(__a1__); \
	Serial.println(__a0__)
#define SERIAL3(__a2__, __a1__, __a0__) \
	Serial.print(__a2__); \
	Serial.print(__a1__); \
	Serial.println(__a0__)
#define SERIAL4(__a3__, __a2__, __a1__, __a0__) \
	Serial.print(__a3__); \
	Serial.print(__a2__); \
	Serial.print(__a1__); \
	Serial.println(__a0__)
#define SERIAL5(__a4__, __a3__, __a2__, __a1__, __a0__) \
	Serial.print(__a4__); \
	Serial.print(__a3__); \
	Serial.print(__a2__); \
	Serial.print(__a1__); \
	Serial.println(__a0__)
#define SERIAL6(__a5__, __a4__, __a3__, __a2__, __a1__, __a0__) \
	Serial.print(__a5__); \
	Serial.print(__a4__); \
	Serial.print(__a3__); \
	Serial.print(__a2__); \
	Serial.print(__a1__); \
	Serial.println(__a0__)


#endif
