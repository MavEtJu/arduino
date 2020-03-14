#ifndef __CONST_H__
#define __CONST_H__

#define DELAY_MEASURE 30000  // 30 seconds per sensor poll
#define DELAY_RADIO     200  // 0.2 seconds per radio poll

#define RADIO_MTU   32
#define RADIO_RETRIES 15
#define RADIO_TIMEOUT 15

enum {
  STATION_CENTRAL,
  STATION_OUTSIDE,
  STATION_ROOF,
  STATION_HANORAH,
  STATION_DIRK,
  STATION_GARAGE,
  STATION_MAX
} addresses;

#define MEASURE_HISTORY 50
struct stationData {
  unsigned long lastPoll;

  float tempCMaxEver, tempCMaxHistory;
  float humidityMaxEver, humidityMaxHistory;
  float heatIndexMaxEver, heatIndexMaxHistory;
  
  float tempCMinEver, tempCMinHistory;
  float humidityMinEver, humidityMinHistory;
  float heatIndexMinEver, heatIndexMinHistory;
  
  float tempC[MEASURE_HISTORY];
  float humidity[MEASURE_HISTORY];
  float heatIndex[MEASURE_HISTORY];
};

typedef struct stationData StationData;

#endif
