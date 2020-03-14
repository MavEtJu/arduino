#ifndef __REMOTE_H__
#define __REMOTE_H__

#include "Station.h"

class Remote : public Station {
  public:
  void loop(void);

  private:
  void setup_station(void);
  void loopSend(void);
};

#endif
