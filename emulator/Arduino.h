
#if !defined(Arduino__h)
#define Arduino__h

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Arduino_types.h"
#include "LED_Types.h"
#include "Serial.h"

#define strcpy_P strcpy
#define memcpy_P memcpy

#define OUTPUT 1
#define HIGH 1
#define LOW 0

const char *PSTR(const char *s);
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t state);
void delay(uint32_t ms);
unsigned long millis(void);

extern Serial Serial;

#define F (char *)


// Default options used for simulator
#define SERIAL_ENABLE
#define MEMORY
#define SIMULATOR

#endif
