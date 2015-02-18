#include <Arduino.h>
#include <StringEncode.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


void
test(void)
{
	StringEncode *enc = new StringEncode();
	int width;
	uint16_t encodedStringPlainLength;
	uint16_t decodedStringPlainLength;
	char encodedStringPlain[100];
	char decodedStringPlain[300];
	char s[300];

	width = 16;
//	encodedStringPlainLength = 16;
//	memcpy(encodedStringPlain,
//	    "\x20\x40\x90\x90\xbf\xd0\xef\x70\x7f\xe0\x3f\xc0\x20\x40\x60\x60",
//	    width * height / 8);
	encodedStringPlainLength = 18;
	memcpy(encodedStringPlain,
	    "\x22\x00\x14\x00\x3e\x00\x6b\x00\xff\x80\xbe\x80\xbe\x80\x14\x00\x36\x00",
	    encodedStringPlainLength);
	enc->DecodePlain(encodedStringPlain, decodedStringPlain,
		encodedStringPlainLength, &decodedStringPlainLength);
	printf("encodedStringPlainLength:%d decodedStringPlainLength:%d\n",
		encodedStringPlainLength, decodedStringPlainLength);
	for (int i = 0; i < decodedStringPlainLength / width; i++) {
		char ss[20];
		strncpy(ss, decodedStringPlain + i * width, width);
		ss[width] = '\0';
		printf("%s\n", ss);
	}

	enc->EncodePlain(decodedStringPlain, s, decodedStringPlainLength,
	    &encodedStringPlainLength);
	printf("memcmp(original, encoded(decoded), %d) = %d\n",
	    encodedStringPlainLength,
	    memcmp(encodedStringPlain, s, encodedStringPlainLength));

	enc->hexdump(encodedStringPlain, encodedStringPlainLength);
	enc->hexdump(s, encodedStringPlainLength);

	enc->DecodePlain(s, decodedStringPlain,
		encodedStringPlainLength, &decodedStringPlainLength);
	for (int i = 0; i < decodedStringPlainLength / width; i++) {
		char ss[20];
		strncpy(ss, decodedStringPlain + i * width, width);
		ss[width] = '\0';
		printf("%s\n", ss);
	}

}

void
process(char *f)
{
	FILE *fin;
	char s[10000], *ps, out[1000], line[100];
	int width, height;
	uint16_t declen, enclen;
	StringEncode *enc = new StringEncode();

	if ((fin = fopen(f, "r")) == NULL)
		return;
	s[0] = '\0';
	ps = s;
	while (!feof(fin)) {
		if (fgets(line, 100, fin) == NULL)
			break;
		line[strlen(line) - 1] = '\0';	// \r
		line[strlen(line) - 1] = '\0';	// |
		while ((strlen(line) - 1) % 8 != 0)
			strcat(line, " ");
		strcat(s, line);
		strcat(s, "|\n");
	}

	ps = strchr(s + 1, '|');
	width = ps - s - 1;

	printf("%s\n", s);
	while ((ps = strchr(s, '|')) != NULL) {
		strcpy(ps, ps + 1);
	}
	while ((ps = strchr(s, '\r')) != NULL) {
		strcpy(ps, ps + 1);
	}
	while ((ps = strchr(s, '\n')) != NULL) {
		strcpy(ps, ps + 1);
	}

	height = strlen(s) / width;
	printf("width: %d\nheight: %d\n", width, height);

	declen = strlen(s);
	enc->EncodePlain(s, out, declen, &enclen);
	enc->hexdump(out, enclen);
}


int
main(int argc, char **argv)
{
	if (argv[1] != NULL) {
		process(argv[1]);
		return 0;
	}
	test();
	return 0;
}
