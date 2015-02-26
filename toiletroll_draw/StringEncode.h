//

#ifndef StringEncode__h
#define StringEncode__h

#include <Arduino.h>

class StringEncodePlain {
	public:
	// Decode a byte value into a "X XX" pattern. Len is the expanded size.
	void encode(const char *in, char *out, uint16_t plainLen,
	    uint16_t *encBits, uint16_t *encBytes);
	void decode(const char *in, char *out, uint16_t bits_in,
	    uint16_t *bytes_out);
};

class StringEncodeMulti {
	public:
	void encode(const char *in, char *out, uint16_t plainLen,
	    uint16_t *encBits, uint16_t *encBytes);
	void decode(const char *in, char *out, uint16_t bits_in,
	    uint16_t *bytes_out);
};

#ifdef SIMULATOR
void hexdump(const char *s, uint16_t len);
#endif

#endif
