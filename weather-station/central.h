#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#include <UTFT.h>

#include "Station.h"

#define MEASURE_HISTORY 50
struct stationData {
  unsigned long lastPoll;

  float tempCMaxEver, tempCMaxHistory;
  float humidityMaxEver, humidityMaxHistory;
  float heatIndexMaxEver, heatIndexMaxHistory;
  
  float tempC[MEASURE_HISTORY];
  float humidity[MEASURE_HISTORY];
  float heatIndex[MEASURE_HISTORY];
};

void setup_lcd(void);

class Central : public Station {
  public:
  void setup(void);
  void loop(void);

  UTFT _lcd;

  private:
  void setup_lcd(void);
  void setup_station(void);
  void Central::updateHistory(int s, float t, float h, float hi);
  void Central::redraw(void);
  void Central::redraw_1(void);

  struct stationData stationData[STATION_MAX];
};

#endif
