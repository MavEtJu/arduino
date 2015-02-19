//
//

#include <stdio.h>
#include <Serial.h>
#include <stdlib.h>
#include <string.h>

#define LOGNR	10
Serial::Serial(void)
{
	// 10k should be enough
	log = (char **)malloc(sizeof(char *) * LOGNR);
	for (int c = 0; c < LOGNR; c++) {
		log[c] = (char *)malloc(sizeof(char) * 50);
		memset(log[c], 0, 49);
	}
	lognr_written = 0;
	lognr_read = 0;
	plog = log[lognr_read];
}

void
Serial::begin(int speed)
{
	// Nothing
}

void
Serial::lognr_increase_read(void)
{
	if (++lognr_read == LOGNR)
		lognr_read = 0;
}

void
Serial::lognr_increase_written(void)
{
	if (++lognr_written == LOGNR)
		lognr_written = 0;
	plog = log[lognr_written];
}

void
Serial::println(const char *s)
{
	strcpy(plog, s);
	plog += strlen(s);
	lognr_increase_written();
}
void
Serial::print(const char *s)
{
	strcpy(plog, s);
	plog += strlen(s);
}

void
Serial::println(char *s)
{
	strcpy(plog, s);
	plog += strlen(s);
	lognr_increase_written();
}
void
Serial::print(char *s)
{
	strcpy(plog, s);
	plog += strlen(s);
}

void
Serial::println(unsigned long ul)
{
	plog += sprintf(plog, "%lu", ul);
	lognr_increase_written();
}
void
Serial::print(unsigned long ul)
{
	plog += sprintf(plog, "%lu", ul);
}

void
Serial::clear(void)
{
	lognr_read = lognr_written;
	plog = log[lognr_written];
}

int
Serial::lines(void)
{
	lognr_read = lognr_written;
	return LOGNR;
}

char *
Serial::get(void)
{
	int prev = lognr_read;
	lognr_increase_read();
	return log[prev];

}
