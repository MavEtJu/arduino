#ifndef __REMOTE_H__
#define __REMOTE_H__

#include "Station.h"

class Remote : public Station {
  public:
  void loop(void);
  void setup(void);

  private:
  void setup_station(void);
  void setup_radio(void);
  void loopSend(void);
  void loopDelay(void);
};

#endif
