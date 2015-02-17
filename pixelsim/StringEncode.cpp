//

#include <Arduino.h>
#include <StringEncode.h>
#include <stdio.h>

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
	switch (ch >> 4) {
	case  0: strcat(out, "    "); break;
	case  1: strcat(out, "   X"); break;
	case  2: strcat(out, "  X "); break;
	case  3: strcat(out, "  XX"); break;
	case  4: strcat(out, " X  "); break;
	case  5: strcat(out, " X X"); break;
	case  6: strcat(out, " XX "); break;
	case  7: strcat(out, " XXX"); break;
	case  8: strcat(out, "X   "); break;
	case  9: strcat(out, "X  X"); break;
	case 10: strcat(out, "X X "); break;
	case 11: strcat(out, "X XX"); break;
	case 12: strcat(out, "XX  "); break;
	case 13: strcat(out, "XX X"); break;
	case 14: strcat(out, "XXX "); break;
	case 15: strcat(out, "XXXX"); break;
	}
	switch (ch & 0xf) {
	case  0: strcat(out, "    "); break;
	case  1: strcat(out, "   X"); break;
	case  2: strcat(out, "  X "); break;
	case  3: strcat(out, "  XX"); break;
	case  4: strcat(out, " X  "); break;
	case  5: strcat(out, " X X"); break;
	case  6: strcat(out, " XX "); break;
	case  7: strcat(out, " XXX"); break;
	case  8: strcat(out, "X   "); break;
	case  9: strcat(out, "X  X"); break;
	case 10: strcat(out, "X X "); break;
	case 11: strcat(out, "X XX"); break;
	case 12: strcat(out, "XX  "); break;
	case 13: strcat(out, "XX X"); break;
	case 14: strcat(out, "XXX "); break;
	case 15: strcat(out, "XXXX"); break;
	}
    }
}

void
StringEncode::hexdump(const char *s, uint16_t len)
{
	for (uint16_t c = 0; c < len; c++) {
		printf("\\x%02x", (unsigned char)s[c]);
	}
	printf("\n");
}
