
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
#define MYCONSTRUCTOR(__t__) \
	__t__(LED_Strip *led, uint16_t VIEW_WIDTH, uint16_t VIEW_HEIGHT)

#endif
