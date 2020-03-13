#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define __STATION_CENTRAL__
#else
#define __STATION_REMOTE__
#endif

#include <SPI.h>
#include <ArduinoUniqueID.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "DHT.h"
#include "printf.h"
#ifdef __STATION_CENTRAL__
#include "UTFT.h"
#endif

#define DELAY_MEASURE 30000  // 30 seconds per sensor poll
#define DELAY_RADIO     200  // 0.2 seconds per radio poll

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
double thHumidity, thTempC, thHeatIndex;

#define RADIO_PIN1  6
#define RADIO_PIN2  7
#define RADIO_MTU   32
#define RADIO_RETRIES 15
#define RADIO_TIMEOUT 15
RF24 radio(RADIO_PIN1, RADIO_PIN2);

#ifdef __STATION_CENTRAL__
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
UTFT myGLCD(ILI9481,38,39,40,41);
#endif

char uniqueID[UniqueIDsize + 1];

enum {
  STATION_CENTRAL,
  STATION_OUTSIDE,
  STATION_ROOF,
  STATION_HANORAH,
  STATION_DIRK,
  STATION_GARAGE,
  STATION_MAX
} addresses;

int stationIndex = 0;
const uint64_t radioChannels[STATION_MAX] = {
  0xF123450000LL,   // Central
  0xF123450001LL,
  0xF123450002LL,
  0xF123450003LL,
  0xF123450004LL,
  0xF123450005LL,
};
const char *uniqueIDs[STATION_MAX] = {
  "x",
  "\x57\x38\x37\x35\x39\x36\x08\x25\x1D",
  "x",
  "x",
  "x",
  "x"
};
const char *stationName[STATION_MAX] = {
  "Central",
  "Outside",
  "Roof",
  "Hanorah",
  "Dirk",
  "Garage",
};


#ifdef __STATION_CENTRAL__
#define MEASURE_HISTORY 50
struct stationData {
  unsigned long lastPoll;

  float tempCMaxEver, tempCMaxHistory;
  float humidityMaxEver, humidityMaxHistory;
  float heatIndexMaxEver, heatIndexMaxHistory;
  
  float tempC[MEASURE_HISTORY];
  float humidity[MEASURE_HISTORY];
  float heatIndex[MEASURE_HISTORY];
};
struct stationData stationData[STATION_MAX];
#endif

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

  setup_dht22();
  setup_station();
  setup_radio();
#ifdef __STATION_CENTRAL__
  setup_lcd();  
#endif
}

#ifdef __STATION_CENTRAL__
void setup_lcd(void)
{
  myGLCD.InitLCD();
  myGLCD.setFont(BigFont);
  myGLCD.clrScr();
}
#endif

void setup_dht22(void)
{
  Serial.println(F("DHT22 initializing"));
  dht.begin();
}

void setup_station(void)
{
  Serial.print(F("Serial number:"));
  uniqueID[0] = 0;
  for (size_t i = 0; i < UniqueIDsize; i++) {
    if (UniqueID[i] < 0x10)
      strcat(uniqueID, "0");
    Serial.print(UniqueID[i], HEX);
  }
  Serial.println(F(""));

#ifdef __STATION_CENTRAL__
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
#endif

#ifdef __STATION_REMOTE__
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
#endif
  Serial.print  (F("Station index: "));
  Serial.println(stationIndex);
}

void setup_radio(void)
{
  Serial.println(F("Radio initializing"));

  radio.begin();
  radio.setRetries(RADIO_RETRIES, RADIO_TIMEOUT);
  radio.setPayloadSize(RADIO_MTU);

#ifdef __STATION_CENTRAL__
  radio.openWritingPipe(radioChannels[STATION_CENTRAL]);
  for (int i = 1; i < STATION_MAX; i++)
    radio.openReadingPipe(i, radioChannels[i]);
#endif
#ifdef __STATION_REMOTE__
  radio.openWritingPipe(radioChannels[stationIndex]);
  radio.openReadingPipe(1, radioChannels[STATION_CENTRAL]);
#endif
  radio.startListening();
  radio.printDetails();
}

void loop(void)
{
#ifdef __STATION_REMOTE__
  loop_remote();
#endif
#ifdef __STATION_CENTRAL__
  loop_central();
#endif
}

#ifdef __STATION_CENTRAL__
void loop_central(void)
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

void updateHistory(int s, float t, float h, float hi)
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

void redraw(void)
{
  redraw_1();
}


//////////////////////////////////////
class window {
  public:
    window(int sizex, int sizey, int offsetx, int offsety);
    void print(char *s, int x, int y);
    void printC(char *s, int y);
    void printF(float f, int x, int y);
    void printFC(float f, int y);
    void printFC7(float f, int y);
  private:
    int _sizex, _sizey, _offsetx, _offsety;  
};

window::window(int sizex, int sizey, int offsetx, int offsety)
{
  // (0, 0) is top left, unlike the display driver where (0, 0) is bottom left.
  _sizex = sizex;
  _sizey = sizey;
  _offsetx = offsetx;
  _offsety = offsety;
}

// +y_size because it draws from the bottom.
#define Y(y) (_offsety + myGLCD.cfont.y_size + (y))
#define X(x) (_offsetx + (x))

void window::print(char *s, int x, int y)
{
  myGLCD.print(s, X(x), Y(y) - myGLCD.cfont.y_size);
}
void window::printC(char *s, int y)
{
  print(s, (_sizex - strlen(s) * myGLCD.cfont.x_size) / 2, y);
}
void window::printF(float f, int x, int y)
{
  char s[10];
  dtostrf(f, 4, 1, s);
  print(s, x, y);
}
void window::printFC(float f, int y)
{
  char s[10];
  dtostrf(f, 4, 1, s);
  printC(s, y);
}
void window::printFC7(float f, int y)
{
  char s[10];
  dtostrf(f, 4, 1, s);
  // remap space to / in the font table
  if (s[0] == ' ')
    s[0] = '/';
  s[2] = '\0';

  // resize for the decimal dot
  int width = 3 * myGLCD.cfont.x_size + 11;
  int x = _sizex / 2 - width / 2;
  print(s, x, y);
  x += 2 * myGLCD.cfont.x_size;
  print(".", x, y);
  x += 11;
  print(s + 3, x, y);
}
//////////////////////////////////////

void redraw_1(void)
{
  int xmax = myGLCD.getDisplayXSize();
  int ymax = myGLCD.getDisplayYSize();

  myGLCD.setColor(240, 0, 0);
  myGLCD.drawRect(0, 0, 20, 20);

  myGLCD.setColor(240, 240, 240);
  myGLCD.drawRect(0, 0, xmax - 1, ymax - 1);
  myGLCD.drawLine(0, ymax / 2, xmax - 1, ymax / 2);
  myGLCD.drawLine(1 * xmax / 3, 0, 1 * xmax / 3, ymax - 1);
  myGLCD.drawLine(2 * xmax / 3, 0, 2 * xmax / 3, ymax - 1);

  int xsize = xmax / 3;
  int ysize = ymax / 2;
  for (int s = 0; s < STATION_MAX; s++) {
    int xoffset = (s % 3) * xmax / 3.0;
    int yoffset = (s / 3) * ymax / 2.0;

    window W = window::window(xsize, ysize, xoffset, yoffset);

    int y = 1;

    // Header
    myGLCD.setFont(BigFont);
    myGLCD.setColor(0, 240, 0);
    W.printC(stationName[s], y);
    y += myGLCD.cfont.y_size;

    // Space
    y += myGLCD.cfont.y_size / 2;

    // Temperature and humidity
    // darker for older information
    // 240 plus sixty seconds leeway, so after 5 minutes it is dark
    int darkness = 240 + 65 - (millis() - stationData[s].lastPoll) / 1000;
    if (darkness < 0)
      darkness = 0;
    if (darkness > 240)
      darkness = 240;

    myGLCD.setColor(darkness, 0, darkness);
    myGLCD.setFont(SmallFont);
    W.printC("Temperature", y);
    y += myGLCD.cfont.y_size;
    myGLCD.setColor(0, 0, darkness);
    myGLCD.setFont(SevenSegNumFont);
    W.printFC7(stationData[s].tempC[MEASURE_HISTORY - 1], y);
    y += myGLCD.cfont.y_size;
    myGLCD.setColor(darkness, 0, darkness);
    myGLCD.setFont(SmallFont);
    W.printC("Humidity", y);
    y += myGLCD.cfont.y_size;
    myGLCD.setColor(0, 0, darkness);
    myGLCD.setFont(SevenSegNumFont);
    W.printFC7(stationData[s].humidity[MEASURE_HISTORY - 1], y);
    y += myGLCD.cfont.y_size;
  }
}

#endif

#ifdef __STATION_REMOTE__
void loop_remote(void)
{
  loopTempHumidity();
  loopSend();
  delay(DELAY_MEASURE);
}

void loopSend(void)
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
  radio.stopListening();
  ok = radio.write(data, strlen(data) + 1);
  radio.startListening();
    
  if (ok)
    Serial.println(F("ok!"));
  else
    Serial.println(F("failed."));
}
#endif

void loopTempHumidity(void)
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

  Serial.print(F("Humidity"));
  Serial.print(thHumidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(thTempC);
  Serial.print(F("°C  Heat index: "));
  Serial.print(thHeatIndex);
  Serial.println(F("°C "));
}
