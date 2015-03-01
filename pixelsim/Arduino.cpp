
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
	static long l0;
	bool first = 1;

	if (first) {
		gettimeofday(&tv, NULL);
		if (tv.tv_usec < 1000) {
			tv.tv_usec += 1000000;
			tv.tv_sec--;
		}
		tv.tv_usec -= 1000;
		l0 = tv.tv_sec * 1000000 + tv.tv_usec;
		l0 /= 1000;
		first = 0;
	}

	gettimeofday(&tv, NULL);
	long l = tv.tv_sec * 1000000 + tv.tv_usec;
	l /= 1000;
	return (l - l0);
}
