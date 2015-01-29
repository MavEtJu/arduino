//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons of
the DFRobot LCD Keypad Shield for Arduino
Product code : RB-Dfr-07
http://www.robotshop.com/dfrobot-lcd-keypad-shield-arduino-1.html

Note cct error identified by Arduino forum discussion at:
http://arduino.cc/forum/index.php/topic,96747.0.html
which advises insertion of a Germanium 1n34a or a Schotky 1N5819
diode between pin 10 and the base of Q1 (K to pin 10).

sample code originally by Mark Bramwell, July 2010
modifications by Dion Weston, March 2012



********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int backLight   = 10;    // LCD Panel Backlight LED connected to digital pin 10
int lightLevel  = 255;   // Initialise light full on
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my [Mark Bramwell's] buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
 return btnNONE;  // when all others fail, return this...
}

void setup()
{
 lcd.begin(16, 2);              // start the LCD library
 lcd.setCursor(0,0);            // move cursor to beginning of line "0"
 lcd.print("Backlight adjust"); // print a simple message
 
}
 
void loop()
{
 analogWrite(backLight, lightLevel);
 lcd.setCursor(13,1);            // move to position 13 on the second line
 lcd.print(lightLevel);

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("LED On          ");
     lightLevel = 255;
     break;
     }
   case btnLEFT:
     {
     lcd.print("LED Off         ");
     lightLevel = 1;
     break;
     }
   case btnUP:
     {
     lcd.print("LED Fade Up     ");
     if (lightLevel < 255) lightLevel += 1;
     break;
     }
   case btnDOWN:
     {
     lcd.print("LED Fade Down   ");
     if (lightLevel > 1) lightLevel -= 1;
     break;
     }
   case btnSELECT:
     {
     lcd.print("Select          ");
     break;
     }
     case btnNONE:
     {
     lcd.print("                ");
     break;
     }
 }
 
}


