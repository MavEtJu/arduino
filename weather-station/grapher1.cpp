#include <math.h>
#include <UTFT.h>
#include "const.h"
#include "window.h"

#include "Grapher1.h"

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else // __ARM__
extern char *__brkval;
#endif // __arm__
int freeMemory() {
char top;
#ifdef __arm__
return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
return &top - __brkval;
#else // __arm__
return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}

void Grapher1::redraw(void)
{
  int xmax = _lcd->getDisplayXSize();
  int ymax = _lcd->getDisplayYSize();

  _lcd->setColor(240, 0, 0);
  _lcd->drawRect(0, 0, 20, 20);

  _lcd->setColor(240, 240, 240);
  _lcd->drawRect(0, 0, xmax - 1, ymax - 1);
  _lcd->drawLine(0, ymax / 2, xmax - 1, ymax / 2);
  _lcd->drawLine(1 * xmax / 3, 0, 1 * xmax / 3, ymax - 1);
  _lcd->drawLine(2 * xmax / 3, 0, 2 * xmax / 3, ymax - 1);

  int xsize = xmax / 3;
  int ysize = ymax / 2;
  for (int s = 0; s < STATION_MAX; s++) {
    int xoffset = (s % 3) * xmax / 3.0;
    int yoffset = (s / 3) * ymax / 2.0;

    window *W = new window(_lcd, xsize, ysize, xoffset, yoffset);
    int y = 1;

    // Header
    _lcd->setFont(BigFont);
    _lcd->setColor(0, 240, 0);
    W->printC(_station->stationName[s], y);
    y += _lcd->cfont.y_size;

    // Space
    y += _lcd->cfont.y_size / 2;

    // Temperature and humidity
    // darker for older information
    // 240 plus sixty seconds leeway, so after 5 minutes it is dark
    int darkness = 240 + 65 - (millis() - _stationData[s].lastPoll) / 1000;
    if (darkness < 0)
      darkness = 0;
    if (darkness > 240)
      darkness = 240;

    _lcd->setColor(darkness, 0, darkness);
    _lcd->setFont(SmallFont);
    W->printC("Temperature", y);
    y += _lcd->cfont.y_size;
    _lcd->setColor(0, 0, darkness);
    _lcd->setFont(SevenSegNumFont);
    W->printFC7(_stationData[s].tempC[MEASURE_HISTORY - 1], y);
    y += _lcd->cfont.y_size;
    _lcd->setColor(darkness, 0, darkness);
    _lcd->setFont(SmallFont);
    W->printC("Humidity", y);
    y += _lcd->cfont.y_size;
    _lcd->setColor(0, 0, darkness);
    _lcd->setFont(SevenSegNumFont);
    W->printFC7(_stationData[s].humidity[MEASURE_HISTORY - 1], y);
    y += _lcd->cfont.y_size;
    
    free(W);
  }
}
