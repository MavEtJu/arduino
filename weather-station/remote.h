#ifndef __REMOTE_H__
#define __REMOTE_H__

#ifndef __STATION_REMOTE__
#error huh
#endif

#include "Station.h"

class Remote : public Station {
  public:
  Remote();
  void loop(void);

  private:
  void setup_station(void);
  void loopSend(void);
};

#endif
