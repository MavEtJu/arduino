#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define __STATION_CENTRAL__
#else
#define __STATION_REMOTE__
#endif

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>
#include <ArduinoPrintf.h>

#include "const.h"
#ifdef __STATION_CENTRAL__
#include <UTFT.h>
#include "window.h"
#include "central.h"
Central station;
#endif
#ifdef __STATION_REMOTE__
#include "remote.h"
Remote station;
#endif

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

  station.setup();
}

void loop(void)
{
  station.loop();
}
