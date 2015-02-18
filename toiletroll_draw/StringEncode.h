//

#ifndef StringEncode__h
#define StringEncode__h

#include <Arduino.h>

class StringEncode {
	public:
	StringEncode(void);

	// Decode a byte value into a "X XX" pattern. Len is the expanded size.
	void EncodePlain(const char *in, char *out, uint16_t plainLen,
	    uint16_t *encBits, uint16_t *encBytes);
	void DecodePlain(const char *in, char *out, uint16_t bits_in,
	    uint16_t *bytes_out);
	void hexdump(const char *s, uint16_t len);
};

#endif
