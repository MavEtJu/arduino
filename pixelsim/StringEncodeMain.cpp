#include <Arduino.h>
#include <StringEncode.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
	StringEncode *enc = new StringEncode();
	char s[257];

	enc->EncodePlain("\x20\x40\x90\x90\xbf\xd0\xef\x70\x7f\xe0\x3f\xc0\x20\x40\x60\x60", s, 16 * 8);
	printf("%s\n", s);

	return 0;
}
