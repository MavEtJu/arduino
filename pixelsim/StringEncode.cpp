//

#include <Arduino.h>
#include <StringEncode.h>

StringEncode::StringEncode(void)
{
    // Nothing
}

void
StringEncode::EncodePlain(const char *in, char *out, uint16_t len)
{
}

void
StringEncode::DecodePlain(const char *in, char *out, uint16_t len)
{
    uint16_t c;
    unsigned char ch;
    out[0] = 0;
    for (c = 0; c < len / 8; c++) {
	ch = in[c];
	Serial.print(ch);
	Serial.print(" ");
	Serial.print(ch >> 4);
	Serial.print(" ");
	Serial.print(ch & 0xf); 
	Serial.print(" ");
	Serial.println(((ch % 256) << 4) >> 4);
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
