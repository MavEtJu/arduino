#include <UTFT.h>
#include "const.h"
#include "window.h"

#include "Grapher2.h"

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

RGB Grapher2::rgb[] = {
  { 240,   0,   0},
  { 240, 240,   0},
  { 240,   0, 240},
  {   0, 240,   0},
  {   0,   0, 240},
  {   0, 240, 240}
};

void Grapher2::redraw(void)
{

  float maxTempHistory[STATION_MAX];
  float minTempHistory[STATION_MAX];
  int validHistory[STATION_MAX];

  #define MARGIN  20
  int xmax = _lcd->getDisplayXSize();
  int ymax = _lcd->getDisplayYSize();
  int xsize = xmax - 2 * MARGIN;
  int ysize = ymax - 2 * MARGIN;

  _lcd->clrScr();
  _lcd->setColor(240, 0, 0);
  _lcd->drawRect(0, 0, MARGIN, MARGIN);

#define TEMP_MAX  50.0
#define TEMP_MIN -15.0
#define TEMP_MARGIN 3.0

  // Find out the minimum/maximum temperature of the data set.
  double maxtemp = VALUE_MIN, mintemp = VALUE_MAX;
  for (int s = 0; s < STATION_MAX; s++) {
    maxTempHistory[s] = VALUE_MIN;
    minTempHistory[s] = VALUE_MAX;
    validHistory[s] = 0;
    for (int h = 1; h < MEASURE_HISTORY; h++) {
      if ((_stationData + s)->tempC[h] == VALUE_NONE)
        continue;
      MIN(minTempHistory[s], (_stationData + s)->tempC[h]);
      MAX(maxTempHistory[s], (_stationData + s)->tempC[h]);
      validHistory[s] = 1;
    }
    MAX(maxtemp, maxTempHistory[s]);
    MIN(mintemp, minTempHistory[s]);
  }

#define X(x) (MARGIN + (x) * (1.0 * xsize / MEASURE_HISTORY))
#define Y(y) (ymax - MARGIN - ((y - (mintemp - TEMP_MARGIN)) * (ysize / (maxtemp - mintemp + 2 *TEMP_MARGIN))))

  // minimums / maximums
  _lcd->setColor(120, 120, 120);
  _lcd->drawLine(X(0), Y(mintemp), X(MEASURE_HISTORY), Y(mintemp));
  _lcd->drawLine(X(0), Y(maxtemp), X(MEASURE_HISTORY), Y(maxtemp));

  for (int s = 0; s < STATION_MAX; s++) {
    if (validHistory[s] == 0)
      continue;

    // Determine how old the data is.
    int darkness = 240 + 65 - (millis() - _stationData[s].lastPoll) / 1000;
    if (darkness < 0)
      darkness = 0;
    if (darkness > 240)
      darkness = 240;
    darkness = 240 - darkness;

    // legend
    int y = MARGIN + s * (_lcd->cfont.y_size + 1);
    int x = MARGIN + 3 * _lcd->cfont.x_size;  // diamond with the colour start here

    _lcd->setColor(rgb[s].red - darkness, rgb[s].green - darkness, rgb[s].blue - darkness);
    _lcd->fillRoundRect(x, y, x + 5, y + 5);

    _lcd->setColor(240 - darkness, 240 - darkness, 240 - darkness);
    _lcd->setFont(SmallFont);
    x += _lcd->cfont.x_size;  // spaces start here
    x += _lcd->cfont.x_size * (_station->stationNameLengthMax - strlen(_station->stationName[s]));  // spaces added
    _lcd->print(_station->stationName[s], x, y);
    x += strlen(_station->stationName[s]) * _lcd->cfont.x_size;  // added station name
    _lcd->print(": ", x, y);
    x += 2 * _lcd->cfont.x_size;
    _lcd->printNumF((_stationData + s)->tempC[MEASURE_HISTORY - 1], 1, x, y);
     x += 4 * _lcd->cfont.x_size;
    _lcd->print("\'C", x, y);
    
    // minimums / maximums
    _lcd->setColor(rgb[s].red / 2 - darkness / 2, rgb[s].green / 2 - darkness / 2, rgb[s].blue / 2 - darkness / 2);
    _lcd->drawLine(X(0), Y(minTempHistory[s]), X(MEASURE_HISTORY), Y(minTempHistory[s]));
    _lcd->drawLine(X(0), Y(maxTempHistory[s]), X(MEASURE_HISTORY), Y(maxTempHistory[s]));
    _lcd->drawLine(X(0), Y((_stationData + s)->tempCMaxEver), X(MEASURE_HISTORY), Y((_stationData + s)->tempCMaxEver));
    _lcd->drawLine(X(0), Y((_stationData + s)->tempCMinEver), X(MEASURE_HISTORY), Y((_stationData + s)->tempCMinEver));

    // station data.
    _lcd->setColor(rgb[s].red - darkness, rgb[s].green - darkness, rgb[s].blue - darkness);
    for (int h = 1; h < MEASURE_HISTORY; h++) {
      float y1 = (_stationData + s)->tempC[h - 1];
      float y2 = (_stationData + s)->tempC[h];

      if (y1 == VALUE_NONE && y2 == VALUE_NONE)
        continue;

      if (y1 == VALUE_NONE) y1 = y2;
      if (y2 == VALUE_NONE) y2 = y1;

      _lcd->drawLine(X(h - 1), Y(y1), X(h), Y(y2));
    }
  }

  // Axis
  _lcd->setColor(240, 240, 240);
  _lcd->drawLine(MARGIN, MARGIN, MARGIN, ymax - MARGIN);
  _lcd->drawLine(MARGIN, ymax - MARGIN, xmax - MARGIN, ymax - MARGIN);

  // Markers on the y-axis.
  _lcd->setFont(SmallFont);
  for (int t = TEMP_MIN; t <= TEMP_MAX; t += 1) {
    if (Y(t) < MARGIN || Y(t) > ymax - MARGIN)
      continue;
    if (t % 5 == 0) {
      _lcd->drawLine(X(0), Y(t), X(-1), Y(t));
      _lcd->printNumI(t, X(0), Y(t));
    } else {
      _lcd->drawLine(X(0), Y(t), X(-0.5), Y(t));
    }
  }

}
