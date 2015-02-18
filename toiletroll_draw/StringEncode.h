//

#ifndef StringEncode__h
#define StringEncode__h

#include <Arduino.h>

class StringEncode {
	public:
	StringEncode(void);

	// Decode a byte value into a "X XX" pattern. Len is the expanded size.
	uint16_t EncodePlain(const char *in, char *out, uint16_t len_in,
	    uint16_t *len_out);
	uint16_t DecodePlain(const char *in, char *out, uint16_t len_in,
	    uint16_t *len_out);
	void hexdump(const char *s, uint16_t len);
};

#endif
