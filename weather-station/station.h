#ifndef __STATION_H__
#define __STATION_H__

#include <ArduinoUniqueID.h>
#include <RF24.h>
#include <DHT.h>
#include "const.h"

class Station {
  public:
  Station(void);
  virtual void setup(void);
  virtual void loop(void);
  
  void setup_station(void);
  void setup_radio(void);
  void setup_dht22(void);
  void loopTempHumidity(void);

  static uint64_t radioChannels[STATION_MAX];
  static char *uniqueIDs[STATION_MAX];
  static char *stationName[STATION_MAX];
  static int stationNameLengthMax;
  int stationIndex;
  RF24 *radio;
  double thHumidity, thTempC, thHeatIndex;

  private:  
  char _uniqueID[UniqueIDsize + 1];
  void detectSerialNumber(void);
  DHT *dht;
};

#endif
