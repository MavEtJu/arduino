#include "remote.h"
#include "LowPower.h"

void Remote::setup(void)
{
  Station::setup_dht22();

  setup_station();
  Serial.print  (F("Station index: "));
  Serial.println(stationIndex);

  setup_radio();
}

void Remote::setup_station(void)
{
  Station::setup_station();

  for (int idx = 0; idx < STATION_MAX; idx++) {
    bool allCorrect = 1;
    for (int i = 0; uniqueIDs[idx][i] != 0; i++) {
      if (uniqueIDs[idx][i] != UniqueID[i]) {
        allCorrect = 0;
        break;
      }
    }
    if (allCorrect != 0) {
      stationIndex = idx;
      break;
    }
  }
}

void Remote::setup_radio(void)
{
  Station::setup_radio();
  
  radio->openWritingPipe(radioChannels[stationIndex]);
  radio->openReadingPipe(1, radioChannels[STATION_CENTRAL]);
  radio->startListening();
  radio->printDetails();
}

void Remote::loop(void)
{
  unsigned long timeout = millis() + DELAY_MEASURE;
  loopTempHumidity();
  loopSend();
  loopDelay();
}

void Remote::loopDelay(void)
{
  delay(100);
  unsigned long d = DELAY_MEASURE / 1000  ;
  while (d > 8) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    d -= 8;
  }
  while (d > 2) {
   LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
   d -= 1;
  }
//  Serial.begin(9600);
}

void Remote::loopSend(void)
{
  Serial.println(F("Sending..."));
  bool ok;
  char data[RADIO_MTU];
  char sTempC[10];
  char sHumidity[10];
  char sHeatIndex[10];

  dtostrf(thTempC, 4, 1, sTempC);
  dtostrf(thHumidity, 4, 1, sHumidity);
  dtostrf(thHeatIndex, 4, 1, sHeatIndex);
  // N=Outside,PN=10161,T=23.0,H=69.0,HI=23.0
  sprintf(data, "N=%d,T=%s,H=%s,HI=%s|", stationIndex, sTempC, sHumidity, sHeatIndex);

  printf("Sending: '%s'\r\n", data);
  radio->stopListening();
  ok = radio->write(data, strlen(data) + 1);
  radio->startListening();
    
  if (ok)
    Serial.println(F("ok!"));
  else
    Serial.println(F("failed."));
}
