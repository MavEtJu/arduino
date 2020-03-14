#include "Station.h"

#define RADIO_PIN1  6
#define RADIO_PIN2  7

#define DHTPIN 2
#define DHTTYPE DHT22

uint64_t Station::radioChannels[] = {
  0xF123450000LL,   // Central
  0xF123450001LL,
  0xF123450002LL,
  0xF123450003LL,
  0xF123450004LL,
  0xF123450005LL,
};

char *Station::uniqueIDs[] = {
  "x",
  "\x57\x38\x37\x35\x39\x36\x08\x25\x1D",
  "x",
  "x",
  "x",
  "x"
};

char *Station::stationName[] = {
  "Central",
  "Outside",
  "Roof",
  "Hanorah",
  "Dirk",
  "Garage",
};

RF24 Station::radio = RF24(RADIO_PIN1, RADIO_PIN2);
DHT Station::dht = DHT(DHTPIN, DHTTYPE);

Station::Station(void)
{
  stationIndex = 0;
}

void Station::setup_dht22(void)
{
  Serial.println(F("DHT22 initializing"));
  dht.begin();
}

void Station::setup_station(void)
{
  Serial.print(F("Serial number:"));
  _uniqueID[0] = 0;
  for (size_t i = 0; i < UniqueIDsize; i++) {
    if (UniqueID[i] < 0x10)
      strcat(_uniqueID, "0");
    Serial.print(UniqueID[i], HEX);
  }
  Serial.println(F(""));
}

void Station::setup_radio(void)
{
  Serial.println(F("Radio initializing"));

  radio.begin();
  radio.setRetries(RADIO_RETRIES, RADIO_TIMEOUT);
  radio.setPayloadSize(RADIO_MTU);
}

void Station::loopTempHumidity(void)
{
  thHumidity = dht.readHumidity();
  thTempC = dht.readTemperature();
  
  if (isnan(thHumidity) || isnan(thTempC)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    thHumidity = 0;
    thTempC = 0;
    thHeatIndex = 0;
    return;
  }

  thHeatIndex = dht.computeHeatIndex(thTempC, thHumidity, false);

  Serial.print(F("Humidity: "));
  Serial.print(thHumidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(thTempC);
  Serial.print(F("°C  Heat index: "));
  Serial.print(thHeatIndex);
  Serial.println(F("°C "));
}
