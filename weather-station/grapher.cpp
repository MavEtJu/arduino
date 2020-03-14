#include "grapher.h"

void Grapher::setup(UTFT lcd, Station *station, StationData *stationData)
{
  _lcd = lcd;
  _station = station;
  _stationData = stationData;
}

void Grapher::redraw(void)
{
  Serial.println(F("Grapher::redraw should not be called"));
}
