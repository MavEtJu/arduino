//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

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


#define nameD 0
#define nameH 1
#define nameP 2
#define nameM 3

int step = 0;
int nameoffset = 0;
int namedirection = 1;

char *clearline = "                ";
char *name = clearline;
char *names[4] = {
  "Dirk",
  "Hanorah",
  "Papa",
  "Mama",
};
char *greeting = clearline;
char *greetings[] = {
  "Greetings!",
  "G'day mate!",
  "Yo yo!",
  "Hello!",
  "Euhm.... hi?",
};


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
 lcd.print("Press a button"); // print a simple message
 
 Serial.begin(9600);
 randomSeed(analogRead(0));
}

void setgreeting()
{
  lcd.setCursor(0, 0);
  lcd.print(clearline);
  
  greeting = greetings[random(sizeof(greetings) / sizeof(char *))];
  lcd.setCursor((strlen(clearline) - strlen(greeting)) / 2, 0);
  lcd.print(greeting);
}
 
void buttons()
{
 lcd_key = read_LCD_buttons();  // read the buttons

 if (lcd_key == btnNONE)
   return;
   
 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     name = names[nameD];
     nameoffset = 0;
     break;
   case btnLEFT:
     name = names[nameH];
     nameoffset = 0;
     break;
   case btnUP:
     name = names[nameM];
     nameoffset = 0;
     break;
   case btnDOWN:
     name = names[nameP];
     nameoffset = 0;
     break;
   case btnSELECT:
     setgreeting();
     break;
 }
 lcd.setCursor(0, 1);
 lcd.print(name);
 
}

int processScroller()
{
  if (step % 4 != 0)
    return true;
    
  if (nameoffset + strlen(name) > strlen(clearline) - 1)
    namedirection = -1;
  if (nameoffset == 0)
    namedirection = 1;
    
  nameoffset += namedirection;

  lcd.setCursor(0, 1);
  lcd.print(clearline);
  lcd.setCursor(nameoffset, 1);
  lcd.print(name);
 
 return true;
}

void loop()
{
 analogWrite(backLight, lightLevel);
 buttons();
 delay(25);
 step++;
 
 processScroller();
}

