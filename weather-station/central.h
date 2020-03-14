#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#ifndef __STATION_CENTRAL__
#error huh
#endif

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
extern struct stationData stationData[STATION_MAX];

void setup_lcd(void);

class Central : public Station {
  public:
  Central(void);
  void setup(void);
  void loop(void);

  UTFT _lcd;

  private:
  void setup_lcd(void);
  void setup_station(void);
  void Central::updateHistory(int s, float t, float h, float hi);
  void Central::redraw(void);
  void Central::redraw_1(void);
};

#endif
