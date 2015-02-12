
#include <Arduino.h>

void setup(void);
void loop(void);

int
main(int argc, char **argv)
{
	setup();
	while (1) {
		loop();
	}
}

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
	usleep(ms);
}

