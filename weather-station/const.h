#ifndef __CONST_H__
#define __CONST_H__

#define DELAY_MEASURE 30000  // 30 seconds per sensor poll
#define DELAY_RADIO     200  // 0.2 seconds per radio poll

#define RADIO_MTU   32
#define RADIO_RETRIES 15
#define RADIO_TIMEOUT 15

#define VALUE_MAX 100
#define VALUE_MIN -100
#define VALUE_NONE -100

#define MAX(a, b) a = (a) < (b) ? (b) : (a)
#define MIN(a, b) a = (a) < (b) ? (a) : (b)

enum {
  STATION_CENTRAL,
  STATION_OUTSIDE,
  STATION_ROOF,
  STATION_HANORAH,
  STATION_DIRK,
  STATION_GARAGE,
  STATION_MAX
} addresses;

#define MEASURE_HISTORY 75
struct stationData {
  unsigned long lastPoll;

  float tempCMaxEver;
  float humidityMaxEver;
  float heatIndexMaxEver;
  float tempCMinEver;
  float humidityMinEver;
  float heatIndexMinEver;

  float tempC[MEASURE_HISTORY];
  float humidity[MEASURE_HISTORY];
  float heatIndex[MEASURE_HISTORY];
};
typedef struct stationData StationData;

struct rgb {
  int red;
  int green;
  int blue;
};
typedef struct rgb RGB;

#endif
