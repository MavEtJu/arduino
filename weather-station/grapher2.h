#ifndef __GRAPHER2_H__
#define __GRAPHER2_H__

#include "Grapher.h"

class Grapher2 : public Grapher {
  public:
  void redraw(void);

  private:
  static RGB rgbs[STATION_MAX];
};

#endif
