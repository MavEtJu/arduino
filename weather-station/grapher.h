#ifndef __GRAPHER_H__
#define __GRAPHER_H__

#include <UTFT.h>
#include "const.h"
#include "Station.h"

int freeMemory();

class Grapher {
  public:
  void setup(UTFT *lcd, Station *station, StationData *stationData);
  virtual void redraw(void);

  UTFT *_lcd;
  Station *_station;
  StationData *_stationData;
};

#endif
