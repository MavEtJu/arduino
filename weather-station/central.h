#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#include <UTFT.h>
#include "Grapher.h"

#include "Station.h"

class Central : public Station {
  public:
  Central::Central(void);
  void setup(void);
  void loop(void);

  UTFT *_lcd;

  private:
  void setup_lcd(void);
  void setup_station(void);
  void setup_radio(void);
  void setup_grapher(void);
  void updateHistory(int s, float t, float h, float hi);
  void redraw(void);

  Grapher *graph;
  StationData *stationData;
};

#endif
