// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include "SFE_BMP180.h"
#include "LiquidCrystal.h"
#include <Wire.h>

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

double baseline; // baseline pressure
double baseheight;

double getPressure();
int secondcounter = 0;
int intro = 10;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  Serial.println("REBOOT");

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin()) {
    Serial.println("BMP180 init success");
    lcd.setCursor(0, 1);
    lcd.print("BMP180 success");
    delay(1000);
  } else {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    lcd.setCursor(0, 1);
    lcd.print("BMP180 failed");
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

  // Get the baseline pressure:
  baseline = getPressure();
  baseheight = pressure.altitude(baseline, baseline);
  
  Serial.print("Baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" millibar");  
  Serial.print("Baseline height: ");
  Serial.println(baseheight);
}

void loop()
{
  double a,P;
  
  // Get a new pressure reading:

  P = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:

  a = pressure.altitude(P, baseline);

  Serial.print("relative altitude: ");
  if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
  Serial.print(a, 1);
  Serial.print(" meters, ");
  if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
  Serial.print(a * 3.28084,0);
  Serial.println(" feet");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Timer: ");
  lcd.print(secondcounter);
  lcd.print(" secs");

  lcd.setCursor(0, 1);
  lcd.print((int)a);
  lcd.print(" meters");

  delay(1000);	// must match the decrement of timeleft which is in seconds
  secondcounter++;
}


double getPressure()
{
  char status;
  double T,P;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status == 0) {
      Serial.println("error starting temperature measurement\n");
      return 0;
  }

  // Wait for the measurement to complete:
  delay(status);

  // Retrieve the completed temperature measurement:
  // Note that the measurement is stored in the variable T.
  // Use '&T' to provide the address of T to the function.
  // Function returns 1 if successful, 0 if failure.

  status = pressure.getTemperature(T);
  if (status == 0) {
    Serial.println("error retrieving temperature measurement\n");
    return 0;
  }

  // Start a pressure measurement:
  // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startPressure(3);
  if (status == 0) {
    Serial.println("error starting pressure measurement\n");
    return 0;
  }

  // Wait for the measurement to complete:
  delay(status);

  // Retrieve the completed pressure measurement:
  // Note that the measurement is stored in the variable P.
  // Use '&P' to provide the address of P.
  // Note also that the function requires the previous temperature measurement (T).
  // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
  // Function returns 1 if successful, 0 if failure.

  status = pressure.getPressure(P,T);
  if (status == 0) {
    Serial.println("error retrieving pressure measurement\n");
    return 0;
  }

  return(P);
}
