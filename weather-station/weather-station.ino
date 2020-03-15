#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define __STATION_CENTRAL__
#else
#define __STATION_REMOTE__
#endif

#include <ArduinoPrintf.h>

#include "const.h"
#ifdef __STATION_CENTRAL__
#include "central.h"
#endif
#ifdef __STATION_REMOTE__
#include "remote.h"
#endif

Station *station;

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

#ifdef __STATION_CENTRAL__
  station = new Central;
#endif
#ifdef __STATION_REMOTE__
  station = new Remote;
#endif

  station->setup();
}

void loop(void)
{
  station->loop();
}
