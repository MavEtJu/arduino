#include <UTFT.h>
#include <ArduinoPrintf.h>

#include "const.h"
#include "Central.h"
#include "Grapher1.h"
#include "Grapher2.h"

struct stationData stationData[STATION_MAX];

Central::Central(void)
{
  stationData = calloc(STATION_MAX, sizeof(StationData));
}

void Central::setup(void)
{
  Station::setup_dht22();

  setup_station();
  Serial.print  (F("Station index: "));
  Serial.println(stationIndex);

  setup_radio();
  setup_lcd();
  setup_grapher();
}

void Central::setup_lcd(void)
{
  _lcd = new UTFT(ILI9481, 38, 39, 40, 41);
  _lcd->InitLCD();
  _lcd->clrScr();
}

void Central::setup_radio(void)
{
  Station::setup_radio();
  Serial.println(F("Radio initializing - Central"));

  radio->openWritingPipe(radioChannels[STATION_CENTRAL]);
  for (int i = 1; i < STATION_MAX; i++)
    radio->openReadingPipe(i, radioChannels[i]);
  radio->startListening();
  radio->printDetails();
}

void Central::setup_station(void)
{
  Station::setup_station();

  for (int s = 0; s < STATION_MAX; s++) {
    stationData[s].lastPoll = millis();
    stationData[s].heatIndexMaxEver = VALUE_MIN;
    stationData[s].tempCMaxEver = VALUE_MIN;
    stationData[s].humidityMaxEver = VALUE_MIN;
    stationData[s].heatIndexMinEver = VALUE_MAX;
    stationData[s].tempCMinEver = VALUE_MAX;
    stationData[s].humidityMinEver = VALUE_MAX;
    for (int i = 0; i < MEASURE_HISTORY; i++) {
      stationData[s].tempC[i] = VALUE_NONE;
      stationData[s].humidity[i] = VALUE_NONE;
      stationData[s].heatIndex[i] = VALUE_NONE;
    }
  }
}

void Central::setup_grapher(void)
{
  graph = new Grapher2();
  graph->setup(_lcd, this, stationData);
}

void Central::loop(void)
{
  static int pollnr = 0;

  if (pollnr++ % (DELAY_MEASURE / DELAY_RADIO) == 0) {
    loopTempHumidity();
    updateHistory(STATION_CENTRAL, thTempC, thHumidity, thHeatIndex);

    // Not needed that often
    Serial.print("Memory: ");
    Serial.println(freeMemory());
  }

  while (radio->available()) {
    char f[RADIO_MTU];
    bool b = radio->read(f, RADIO_MTU);

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
  memcpy(stationData[s].tempC, stationData[s].tempC + 1, sizeof(float) * (MEASURE_HISTORY - 1));
  memcpy(stationData[s].humidity,  stationData[s].humidity + 1, sizeof(float) * (MEASURE_HISTORY - 1));
  memcpy(stationData[s].heatIndex, stationData[s].heatIndex + 1, sizeof(float) * (MEASURE_HISTORY - 1));
  stationData[s].tempC[MEASURE_HISTORY - 1] = t;
  stationData[s].humidity[MEASURE_HISTORY - 1] = h;
  stationData[s].heatIndex[MEASURE_HISTORY - 1] = hi;

  MAX(stationData[s].tempCMaxEver, t);
  MAX(stationData[s].humidityMaxEver, h);
  MAX(stationData[s].heatIndexMaxEver, hi);
  MIN(stationData[s].tempCMinEver, t);
  MIN(stationData[s].humidityMinEver, h);
  MIN(stationData[s].heatIndexMinEver, hi);
  
  graph->redraw();
}
