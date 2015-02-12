
#if !defined(Arduino__h)
#define Arduino__h

#include <sys/types.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Serial.h"

typedef uint8_t byte;
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef int8_t int8_t;
typedef int16_t int16_t;
typedef int32_t int32_t;

#define strcpy_P strcpy

#define OUTPUT 1
#define HIGH 1
#define LOW 0

const char *PSTR(const char *s);
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t state);
void delay(uint32_t ms);

#endif
