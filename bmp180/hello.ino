#include "LiquidCrystal.h"

int counter = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(void)
{
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop(void)
{
  lcd.setCursor(0, 1);
  lcd.print(counter / 10);
}
