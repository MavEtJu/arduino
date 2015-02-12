#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdio.h>

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800)
{
	pixels = (char *)malloc(sizeof(char) * n * 3);
}


void
Adafruit_NeoPixel::begin(void)
{
}

void
Adafruit_NeoPixel::show(void)
{
	printf("Adafruit_NeoPixel:show\n");
}
