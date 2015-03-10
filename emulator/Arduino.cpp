
#include <Arduino.h>
#include <time.h>
#include <Serial.h>
#include <sys/time.h>

void setup(void);
void loop(void);
class Serial Serial;

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
	struct timeval tv;
	static time_t sec0;
	static bool first = 1;
	unsigned long l;

	if (first) {
		gettimeofday(&tv, NULL);
		sec0 = tv.tv_sec;
		first = 0;
	}

	gettimeofday(&tv, NULL);
	l = (tv.tv_sec - sec0) * 1000 + (tv.tv_usec / 1000);
	return l;
}
