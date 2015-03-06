
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
    Serial.print(f); \
    Serial.print(F(": FreeRam(): ")); \
    Serial.println(freeRam()); 

#define FREEMEMORY(T) \
    Serial.print(T); \
    Serial.print(F(": freeMemory(): ")); \
    Serial.println(freeMemory());

#endif
