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
	uint16_t encbytes1, encbits1, decbytes1, encbytes2, encbits2, decbytes2;
	char encstring1[100], encstring2[100];
	char decstring1[300], decstring2[300];

	/* Decoding test */
	width = 16;
//	encodedStringPlainLength = 16;
//	memcpy(encodedStringPlain,
//	    "\x20\x40\x90\x90\xbf\xd0\xef\x70\x7f\xe0\x3f\xc0\x20\x40\x60\x60",
//	    width * height / 8);
//	encodedStringPlainLength = 18;
//	memcpy(encodedStringPlain,
//	    "\x22\x00\x14\x00\x3e\x00\x6b\x00\xff\x80\xbe\x80\xbe\x80\x14\x00\x36\x00",
//	    encodedStringPlainLength);

	width = 9;
	encbytes1 = 8;
	encbits1 = 63;
	memcpy(encstring1, "\x1c\x1f\x1f\xdb\xb2\xa2\xea\xaa", encbits1);
	printf("--Decoding\n");
	printf("width: %d\nencbytes1: %d\nencbits1: %d\n", width, encbytes1,
	    encbits1);

	enc->DecodePlain(encstring1, decstring1, encbits1, &decbytes1);
	enc->hexdump(encstring1, encbytes1);

	printf("decbytes1:%d\n", decbytes1);
	printf("decstring1:|%s|\n", decstring1);

	for (int i = 0; i < decbytes1; i += width) {
		char ss[20];
		memset(ss, 0, sizeof(ss));
		strncpy(ss, decstring1 + i, width);
		printf("|%s|\n", ss);
	}


	/* Encoding test */
	printf("--Encoding\n");
	enc->EncodePlain(decstring1, encstring2, decbytes1, &encbits2, &encbytes2);

	printf("decbytes1: %d\nencbits2: %d\nencbytes2: %d\n",
	    decbytes1, encbits2, encbytes2);
	printf("encstring2: ");
	enc->hexdump(encstring2, encbytes2);
	printf("\n");

	printf("memcmp(original, encoded(decoded), %d) = %d\n",
	    encbytes1,
	    memcmp(encstring1, encstring2, encbytes1));

	enc->hexdump(encstring1, encbytes1);
	enc->hexdump(encstring2, encbytes2);

	enc->DecodePlain(encstring2, decstring2, encbits2, &decbytes2);
	for (int i = 0; i < decbytes2; i+= width) {
		char ss[20];
		memset(ss, 0, sizeof(ss));
		strncpy(ss, decstring2 + i, width);
		printf("|%s|\n", ss);
	}

}

void
process(char *f)
{
	FILE *fin;
	char s[10000], *ps, out[1000], line[100], *pline;
	int width, height;
	uint16_t declen, encbits, encbytes;
	StringEncode *enc = new StringEncode();

	if ((fin = fopen(f, "r")) == NULL)
		return;
	s[0] = '\0';
	ps = s;
	while (!feof(fin)) {
		if (fgets(line, 100, fin) == NULL)
			break;
		if (strchr(line, '|') == NULL)
			continue;
		strcpy(line, strchr(line, '|') + 1);
		if ((pline = strchr(line, '|')) == NULL)
			continue;;
		*pline = '\0';
		width = strlen(line);
		strcat(s, line);
	}

	printf("width: %d\n", width);
	printf("%s\n", s);
	height = strlen(s) / width;

	declen = strlen(s);
	enc->EncodePlain(s, out, declen, &encbits, &encbytes);
	enc->hexdump(out, encbytes);
	printf("width: %d\nheight: %d\ndeclen: %d\nencbits: %d\nencbytes: %d\n", width, height, declen, encbits, encbytes);
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
