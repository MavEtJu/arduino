
//
//

#if !defined A_Tools__h
#define A_Tools__h

/* https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory */
int freeRam(void);

#define FREERAM(f) \
    Serial.print(f); \
    Serial.print(F(": FreeRAM: ")); \
    Serial.println(freeRam()); 

#define FREEMEMORY(T) \
    Serial.print(T); \
    Serial.print(F(": ")); \
    Serial.println(freeMemory());

#endif
