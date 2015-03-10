#include <Arduino.h>
#include <StringEncode.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "A_Tools.h"

void
printText(char *decstring1, int width)
{
	for (int i = 0; i < strlen(decstring1); i+= width) {
		char ss[20];
		memset(ss, 0, sizeof(ss));
		strncpy(ss, decstring1 + i, width);
		printf("|%s|\n", ss);
	}
}

void
testPlain(void)
{
	StringEncodePlain *enc = new StringEncodePlain();
	int width;
	uint16_t encbytes1, encbits1, decbytes1, encbytes2, encbits2, decbytes2;
	char encstring1[300], encstring2[300];
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
	printf("--DecodingPlain\n");
	printf("width: %d\nencbytes1: %d\nencbits1: %d\n", width, encbytes1,
	    encbits1);

	enc->decode(encstring1, decstring1, encbits1, &decbytes1);
	hexdump(encstring1, encbytes1);

	printf("decbytes1:%d\n", decbytes1);
	printf("decstring1:|%s|\n", decstring1);

	for (int i = 0; i < decbytes1; i += width) {
		char ss[20];
		memset(ss, 0, sizeof(ss));
		strncpy(ss, decstring1 + i, width);
		printf("|%s|\n", ss);
	}


	/* Encoding test */
	printf("\n--EncodingPlain\n");
	enc->encode(decstring1, encstring2, decbytes1, &encbits2, &encbytes2);

	printf("decbytes1: %d\nencbits2: %d\nencbytes2: %d\n",
	    decbytes1, encbits2, encbytes2);
	printf("encstring2: ");
	hexdump(encstring2, encbytes2);
	printf("\n");

	printf("memcmp(original, encoded(decoded), %d) = %d\n",
	    encbytes1,
	    memcmp(encstring1, encstring2, encbytes1));

	hexdump(encstring1, encbytes1);
	hexdump(encstring2, encbytes2);

	enc->decode(encstring2, decstring2, encbits2, &decbytes2);
	printText(decstring2, width);
}

void
testMulti3(void)
{
	StringEncodeMulti *enc = new StringEncodeMulti();
	int width;
	uint16_t encbytes1, encbits1, decbytes1, decbytes2;
	char encstring1[300];
	char decstring1[300], decstring2[300];

	printf("\n--EncodingMulti2\n");
	strcpy(decstring1, "     ......        ..RRRRWW..   ");

	width = 16;
	printText(decstring1, width);
	decbytes1 = strlen(decstring1);
	enc->encode(decstring1, encstring1, decbytes1, &encbits1, &encbytes1);

	printf("decbytes1: %d\nencbits1: %d\nencbytes1: %d\n",
	    decbytes1, encbits1, encbytes1);
	printf("encstring1: ");
	hexdump(encstring1, encbytes1);
	printf("\n");

	printf("\n");
	enc->decode(encstring1, decstring2, encbits1, &decbytes2,
	    sizeof(decstring2));
	printf("decbytes2: %d\n", decbytes2);
	for (int i = 0; i < decbytes2; i+= width) {
		char ss[20];
		memset(ss, 0, sizeof(ss));
		strncpy(ss, decstring2 + i, width);
		printf("|%s|\n", ss);
	}

}

char *
readFile(char *f, int *width)
{
	FILE *fin;
	static char s[10000];
	char *ps, line[100], *pline, del;

	if ((fin = fopen(f, "r")) == NULL)
		return NULL;
	s[0] = '\0';
	ps = s;
	while (!feof(fin)) {
		if (fgets(line, 100, fin) == NULL)
			break;
		del = '\0';
		if (strchr(line, '|') != NULL)
			del = '|';
		if (strchr(line, '\"') != NULL)
			del = '\"';
		if (del == '\0')
			continue;
		strcpy(line, strchr(line, del) + 1);
		if ((pline = strchr(line, del)) == NULL)
			continue;;
		*pline = '\0';
		*width = strlen(line);
		strcat(s, line);
	}
	return s;
}

void
processPlain(char *f)
{
	int height, width;
	uint16_t declen, encbits, encbytes;
	StringEncodePlain *enc = new StringEncodePlain();
	char out[1000];

	char *s = readFile(f, &width);
	printf("width: %d\n", width);
	printf("%s\n", s);
	height = strlen(s) / width;

	declen = strlen(s);
	enc->encode(s, out, declen, &encbits, &encbytes);
	printf("Plain:\nwidth: %d\nheight: %d\ndeclen: %d\nencbits: %d\nencbytes: %d\n", width, height, declen, encbits, encbytes);
	hexdump(out, encbytes);
}

void
processMulti(char *f)
{
	FILE *fin;
	char s[10000], *ps, out[1000], line[100], *pline, del;
	int width, height;
	uint16_t declen, encbits, encbytes;
	StringEncodeMulti *enc = new StringEncodeMulti();

	if ((fin = fopen(f, "r")) == NULL)
		return;
	s[0] = '\0';
	ps = s;
	while (!feof(fin)) {
		if (fgets(line, 100, fin) == NULL)
			break;
		del = '\0';
		if (strchr(line, '|') != NULL)
			del = '|';
		if (strchr(line, '\"') != NULL)
			del = '\"';
		if (del == '\0')
			continue;
		strcpy(line, strchr(line, del) + 1);
		if ((pline = strchr(line, del)) == NULL)
			continue;;
		*pline = '\0';
		width = strlen(line);
		strcat(s, line);
	}

	printf("width: %d\n", width);
	printf("%s\n", s);
	height = strlen(s) / width;

	declen = strlen(s);
	enc->encode(s, out, declen, &encbits, &encbytes);
	printf("\nMulti:\nwidth: %d\nheight: %d\ndeclen: %d\nencbits: %d\nencbytes: %d\n", width, height, declen, encbits, encbytes);
	hexdump(out, encbytes);
}


int
main(int argc, char **argv)
{
	if (argv[1] != NULL) {
		processPlain(argv[1]);
		processMulti(argv[1]);
		return 0;
	}

	testPlain();
	testMulti3();
	return 0;
}
