//

#include <Arduino.h>
#include "StringEncode.h"
#ifdef SIMULATOR
# include <stdio.h>
#endif

StringEncode::StringEncode(void)
{
    // Nothing
}

void
StringEncode::EncodePlain(const char *in, char *out, uint16_t plainLen)
{
    uint16_t c;
    uint16_t bits[8];

    // printf("plainLen:%d\n", plainLen);
    for (c = 0; c < plainLen; c += 8) {
	// printf("c:%d\n", c);
	bits[7] = in[c + 0] != ' ';
	bits[6] = in[c + 1] != ' ';
	bits[5] = in[c + 2] != ' ';
	bits[4] = in[c + 3] != ' ';
	bits[3] = in[c + 4] != ' ';
	bits[2] = in[c + 5] != ' ';
	bits[1] = in[c + 6] != ' ';
	bits[0] = in[c + 7] != ' ';
	out[c / 8] = (bits[7] << 7) + (bits[6] << 6) + (bits[5] << 5) +
		     (bits[4] << 4) + (bits[3] << 3) + (bits[2] << 2) +
		     (bits[1] << 1) + bits[0];
	// printf("x:%x\n", out[c/8]);
    }
}

void
StringEncode::DecodePlain(const char *in, char *out, uint16_t encodedLen)
{
    uint16_t c;
    unsigned char ch;

    out[0] = 0;
    for (c = 0; c < encodedLen; c++) {
	ch = in[c];
	for (int8_t i = 7; i >= 0; i--) {
	    if ((ch >> i) % 2 != 0)
		strcat(out, "X");
	    else
		strcat(out, " ");
	}
    }
}

void
StringEncode::hexdump(const char *s, uint16_t len)
{
#ifdef SIMULATOR
    for (uint16_t c = 0; c < len; c++) {
	printf("\\x%02x", (unsigned char)s[c]);
    }
    printf("\n");
#endif
}
