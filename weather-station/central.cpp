#include <UTFT.h>
#include <ArduinoPrintf.h>

#include "const.h"
#include "central.h"
#include "window.h"

struct stationData stationData[STATION_MAX];

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

void Central::setup(void)
{
  Station::setup();
  setup_lcd();
}

void Central::setup_lcd(void)
{
  _lcd = UTFT(ILI9481,38,39,40,41);
  _lcd.InitLCD();
  _lcd.setFont(BigFont);
  _lcd.clrScr();
}

void Central::setup_station(void)
{
  Station::setup_station();

  for (int s = 0; s < STATION_MAX; s++) {
    stationData[s].lastPoll = millis();
    stationData[s].heatIndexMaxEver = 0;
    stationData[s].heatIndexMaxHistory = 0;
    stationData[s].tempCMaxEver = 0;
    stationData[s].tempCMaxHistory = 0;
    stationData[s].humidityMaxEver = 0;
    stationData[s].humidityMaxHistory = 0;
    for (int i = 0; i < MEASURE_HISTORY; i++) {
      stationData[s].tempC[i] = 0;
      stationData[s].humidity[i] = 0;
      stationData[s].heatIndex[i] = 0;
    }
  }  
}

void Central::loop(void)
{
  static int pollnr = 0;

  if (pollnr++ % (DELAY_MEASURE / DELAY_RADIO) == 0) {
    loopTempHumidity();
    updateHistory(STATION_CENTRAL, thTempC, thHumidity, thHeatIndex);
  }

  while (radio.available()) {
    char f[RADIO_MTU];
    bool b = radio.read(f, RADIO_MTU);

    if (b) {
      printf("---%s---\n\r", f);
      char *s;
      char *sI, *sT, *sH, *sHI;
      sI = f;
      s = strchr(f, ','); *s = '\0'; s++; sT = s;
      s = strchr(s, ','); *s = '\0'; s++; sH = s;
      s = strchr(s, ','); *s = '\0'; s++; sHI = s;
      s = strchr(s, '|'); *s = '\0';
      sI += 2;
      sT += 2;
      sH += 2;
      sHI += 3;
      updateHistory(atoi(sI), atof(sT), atof(sH), atof(sHI));

      printf("---%s---%s---%s---%s---\n\r", sI, sT, sH, sHI);
    }
  }

  delay(DELAY_RADIO);
}

void Central::updateHistory(int s, float t, float h, float hi)
{
  printf("Updating %d\n\r", s),
  stationData[s].lastPoll = millis();
  memcpy(stationData[s].tempC, stationData[s].tempC + sizeof(float), sizeof(float) * (MEASURE_HISTORY - 1));
  memcpy(stationData[s].humidity,  stationData[s].humidity + sizeof(float), sizeof(float) * (MEASURE_HISTORY - 1));
  memcpy(stationData[s].heatIndex, stationData[s].heatIndex + sizeof(float), sizeof(float) * (MEASURE_HISTORY - 1));
  stationData[s].tempC[MEASURE_HISTORY - 1] = t;
  stationData[s].humidity[MEASURE_HISTORY - 1] = h;
  stationData[s].heatIndex[MEASURE_HISTORY - 1] = hi;

  redraw();
}

void Central::redraw(void)
{
  redraw_1();
}

void Central::redraw_1(void)
{
  int xmax = _lcd.getDisplayXSize();
  int ymax = _lcd.getDisplayYSize();

  _lcd.setColor(240, 0, 0);
  _lcd.drawRect(0, 0, 20, 20);

  _lcd.setColor(240, 240, 240);
  _lcd.drawRect(0, 0, xmax - 1, ymax - 1);
  _lcd.drawLine(0, ymax / 2, xmax - 1, ymax / 2);
  _lcd.drawLine(1 * xmax / 3, 0, 1 * xmax / 3, ymax - 1);
  _lcd.drawLine(2 * xmax / 3, 0, 2 * xmax / 3, ymax - 1);

  int xsize = xmax / 3;
  int ysize = ymax / 2;
  for (int s = 0; s < STATION_MAX; s++) {
    int xoffset = (s % 3) * xmax / 3.0;
    int yoffset = (s / 3) * ymax / 2.0;

    window W = window::window(&_lcd, xsize, ysize, xoffset, yoffset);

    int y = 1;

    // Header
    _lcd.setFont(BigFont);
    _lcd.setColor(0, 240, 0);
    W.printC(stationName[s], y);
    y += _lcd.cfont.y_size;

    // Space
    y += _lcd.cfont.y_size / 2;

    // Temperature and humidity
    // darker for older information
    // 240 plus sixty seconds leeway, so after 5 minutes it is dark
    int darkness = 240 + 65 - (millis() - stationData[s].lastPoll) / 1000;
    if (darkness < 0)
      darkness = 0;
    if (darkness > 240)
      darkness = 240;

    _lcd.setColor(darkness, 0, darkness);
    _lcd.setFont(SmallFont);
    W.printC("Temperature", y);
    y += _lcd.cfont.y_size;
    _lcd.setColor(0, 0, darkness);
    _lcd.setFont(SevenSegNumFont);
    W.printFC7(stationData[s].tempC[MEASURE_HISTORY - 1], y);
    y += _lcd.cfont.y_size;
    _lcd.setColor(darkness, 0, darkness);
    _lcd.setFont(SmallFont);
    W.printC("Humidity", y);
    y += _lcd.cfont.y_size;
    _lcd.setColor(0, 0, darkness);
    _lcd.setFont(SevenSegNumFont);
    W.printFC7(stationData[s].humidity[MEASURE_HISTORY - 1], y);
    y += _lcd.cfont.y_size;
  }
}
