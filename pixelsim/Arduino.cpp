
#include <Arduino.h>
#include <time.h>
#include <Serial.h>

void setup(void);
void loop(void);
class Serial Serial;
time_t time_0 = time(NULL);

const char *
PSTR(const char *s)
{
	return s;
}

void
digitalWrite(uint8_t pin, uint8_t state)
{
	// Nothing!
}

void
pinMode(uint8_t pin, uint8_t mode)
{
	// Nothing!
}

void
delay(uint32_t ms)
{
	usleep(ms * 1000);
}

unsigned long
millis(void)
{
	return (time(NULL) - time_0) * 1000;
}
