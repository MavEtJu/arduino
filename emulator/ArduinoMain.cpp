#include <Arduino.h>

extern void setup(void);
extern void loop(void);

int
main(int argc, char **argv)
{
	setup();
	while (1) {
		loop();
	}
}
