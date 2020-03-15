#include <UTFT.h>
#include "window.h"

window::window(UTFT *lcd, int sizex, int sizey, int offsetx, int offsety)
{
  _lcd = lcd;
  // (0, 0) is top left, unlike the display driver where (0, 0) is bottom left.
  _sizex = sizex;
  _sizey = sizey;
  _offsetx = offsetx;
  _offsety = offsety;
}

// +y_size because it draws from the bottom.
#define Y(y) (_offsety + _lcd->cfont.y_size + (y))
#define X(x) (_offsetx + (x))

void window::print(char *s, int x, int y)
{
  _lcd->print(s, X(x), Y(y) - _lcd->cfont.y_size);
}

void window::printC(char *s, int y)
{
  print(s, (_sizex - strlen(s) * _lcd->cfont.x_size) / 2, y);
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
  int width = 3 * _lcd->cfont.x_size + 11;
  int x = _sizex / 2 - width / 2;
  print(s, x, y);
  x += 2 * _lcd->cfont.x_size;
  print(".", x, y);
  x += 11;
  print(s + 3, x, y);
}
