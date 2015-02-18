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
StringEncode::EncodePlain(const char *in, char *out, uint16_t plainBytes, uint16_t *encodedBits, uint16_t *encodedBytes)
{
    uint16_t c, i;
    uint16_t bits[8];

    *encodedBits = 0;
    *encodedBytes = 0;
    for (c = 0; c < plainBytes; c += 8) {
	// printf("c:%d\n", c);
	memset(bits, 0, sizeof(bits));
	for (i = 0; i < 8; i++) {
	    if (c + i < plainBytes) {
		bits[7-i] = in[c + i] != ' ';
		(*encodedBits)++;
	    }
	}
	if (out != NULL)
	    out[c / 8] = (bits[7] << 7) + (bits[6] << 6) + (bits[5] << 5) +
			 (bits[4] << 4) + (bits[3] << 3) + (bits[2] << 2) +
			 (bits[1] << 1) + bits[0];
	// printf("x:%x\n", out[c/8]);
	(*encodedBytes)++;
    }
}

void
StringEncode::DecodePlain(const char *in, char *out, uint16_t encodedBits, uint16_t *decodedBytes)
{
    uint16_t c;
    unsigned char ch;

    *decodedBytes = 0;

    if (out != NULL)
	out[0] = 0;
    for (c = 0; c < encodedBits; c += 8) {
	ch = in[c / 8];
	for (int8_t i = 7; i >= 0; i--) {
	    if (c + (7 - i) < encodedBits) {
		if (out != NULL) {
		    if ((ch >> i) % 2 != 0)
			strcat(out, "X");
		    else
			strcat(out, " ");
		}
		(*decodedBytes)++;
	    }
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
