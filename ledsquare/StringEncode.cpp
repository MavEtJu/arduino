//

#include <Arduino.h>
#include "StringEncode.h"
#include "A_Tools.h"
#ifdef SIMULATOR
# include <stdio.h>
# include <assert.h>
#endif
#ifdef DEBUG_MEMORY
# include <MemoryFree.h>
#endif

#ifdef SIMULATOR
void
StringEncodePlain::encode(const char *in, char *out, uint16_t plainBytes, uint16_t *encodedBits, uint16_t *encodedBytes)
{
    uint16_t c, i;
    uint16_t bits[8];

    *encodedBits = 0;
    *encodedBytes = 0;
    for (c = 0; c < plainBytes; c += 8) {
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
	(*encodedBytes)++;
    }
}
#endif

void
StringEncodePlain::decode(const char *in, char *out, uint16_t encodedBits, uint16_t *decodedBytes)
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

#ifdef SIMULATOR
char *
_bits(uint8_t b)
{
	char *s = (char *)malloc(12);
	for (uint8_t i = 0; i < 8; i++) {
		s[7 - i] = (b % 2 == 0) ? '0' : '1';
		b /= 2;
	}
	s[8] = '\0';
	return s ;
}
#endif

#ifdef SIMULATOR
void
StringEncodeMulti::encode(const char *in, char *out, uint16_t plainLen,
	    uint16_t *encBits, uint16_t *encBytes)
{
    uint8_t alphabet[128];
    uint16_t letters;
    uint8_t bits;
    uint8_t bitnumbers[128];
    uint8_t bitnumber;
    char *pout = out;

    memset(alphabet, 0, sizeof(alphabet));
    letters = 0;
    for (uint16_t i = 0; i < plainLen; i++) {
        if (alphabet[in[i]] == 0)
	    letters++;
        alphabet[in[i]] = 1;
    }

    bits = 8;
    if (letters <= 128) bits = 7;
    if (letters <=  64) bits = 6;
    if (letters <=  32) bits = 5;
    if (letters <=  16) bits = 4;
    if (letters <=   8) bits = 3;
    if (letters <=   4) bits = 2;
    if (letters <=   2) bits = 1;
    assert(letters <= 32);
    //printf("\nbits: %d\n", bits);

    //printf("Alphabet: 0x%x \"", letters);
    *pout = letters;
    pout++;
    *encBytes = 1;

    bitnumber = 0;
    memset(bitnumbers, 0, sizeof(bitnumbers));
    for (uint8_t i = 0; i < 128; i++) {
	if (alphabet[i] != 0) {
	    *pout = i;
	    pout++;
	    (*encBytes)++;
	    //printf("%c", i);
	    bitnumbers[i] = bitnumber++;
	}
    }
    //printf("\"\n");

    memset(pout, 0, plainLen);
    *encBits = 0;
    for (uint16_t i = 0; i < plainLen; i++) {
	uint8_t c = bitnumbers[in[i]];
	uint8_t byteoffset = *encBits / 8;
	uint8_t bitoffset = *encBits % 8;
	uint8_t left, right;
	
	left = c << (bitoffset);
	right = c >> (8 - bitoffset);
	pout[byteoffset] ^= left;
	if (bitoffset >= bits)
	    pout[byteoffset + 1] ^= right;

	//printf("%2d: %c %d %d:%d %s:%s %s:%s\n",
	//    i, in[i], c, bitoffset, 8 - bitoffset,
	//    _bits(left), _bits(right),
	//    _bits(pout[byteoffset]), _bits(pout[byteoffset + 1]));
	*encBits += bits;
    }

    *encBytes += *encBits / 8;
    if (*encBits % 8 != 0)
	(*encBytes)++;
}
#endif

//#define DEBUG_MEMORY

void
StringEncodeMulti::decode(const char *in, char *out, uint16_t bits_in,
	    uint16_t *bytes_out, uint16_t max_bytes_out)
{
    uint8_t letters, bits;
    uint8_t *alphabet;
    const char *pin = in;
    uint8_t left, right, bitmask;
    uint8_t bits_left, bits_right, i;
    uint16_t bit_offset = 0;

#ifdef DEBUG_MEMORY
    FREERAM("StringEncodeMulti::decode");
#endif
    
    *bytes_out = 0;
    
    letters = in[0];
    pin++;

    bits = 5;
    if (letters <=  32) bits = 5;
    if (letters <=  16) bits = 4;
    if (letters <=   8) bits = 3;
    if (letters <=   4) bits = 2;
    if (letters <=   2) bits = 1;
    //printf("Bits: %d\n", bits);

    bitmask = 0;
    for (uint8_t b = 0; b < bits; b++) {
	bitmask = 1 + (bitmask << 1);
    }

#ifdef DEBUG_MEMORY
    Serial.print(F("Allocating an alphabet of "));
    Serial.print(letters);
    Serial.println(F(" bytes"));
#endif
    alphabet = (uint8_t *)malloc(letters * sizeof(char));
    if (alphabet == NULL) {
	Serial.print(F("alphabet==NULL: Failed to allocate "));
	Serial.print(letters);
	Serial.println(F(" bytes"));
#ifdef DEBUG_MEMORY
	FREEMEMORY("alphabet==NULL");
	FREERAM("alphabet==NULL");
#endif
	return;
    }
    memset(alphabet, '\0', letters * sizeof(uint8_t));
    for (uint8_t c = 0; c < letters; c++) {
	alphabet[c] = in[1 + c];
	printf("%c", in[1 + c]);
	pin++;
    }

    for (bit_offset = 0; bit_offset < bits_in; bit_offset += bits) {
	left = pin[bit_offset / 8];
	right = pin[1 + bit_offset / 8];

	/*
	 * 76543210 76543210
	 */

	bits_left = bit_offset % 8;
	bits_right = 0;
	if (bits_left + bits > 7) {
		bits_right = bits + bits_left - 8;
	}

	i = (left >> (bits_left)) & bitmask;
	if (bits_right) {
	    uint8_t r = right;
	    r <<= 8 - bits_right;
	    r &= 0xff;
	    r >>= 8 - bits_right;
	    r <<= bits - bits_right;
	    r &= 0xff;
	    i += r;
	}

        *out = alphabet[i];
	out++;
	(*bytes_out)++;
        if (*bytes_out == max_bytes_out) {
            Serial.println(F("Reached max_bytes_out"));
            goto bye;
        }
    }

bye:
    free(alphabet);
}

#ifdef SIMULATOR
void
hexdump(const char *s, uint16_t len)
{
    for (uint16_t c = 0; c < len; c++) {
	printf("\\x%02x", (unsigned char)s[c]);
    }
    printf("\n");
}
#endif

