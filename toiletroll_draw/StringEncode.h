//

#ifndef StringEncode__h
#define StringEncode__h

#include <Arduino.h>

class StringEncode {
	public:
	StringEncode(void);

	// Decode a byte value into a "X XX" pattern. Len is the expanded size.
	void EncodePlain(const char *in, char *out, uint16_t len);
	void DecodePlain(const char *in, char *out, uint16_t len);
	void hexdump(const char *s, uint16_t len);
};

#endif
