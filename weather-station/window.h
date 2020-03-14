#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <UTFT.h>

class window {
  public:
    window(UTFT *lcd, int sizex, int sizey, int offsetx, int offsety);
    void print(char *s, int x, int y);
    void printC(char *s, int y);
    void printF(float f, int x, int y);
    void printFC(float f, int y);
    void printFC7(float f, int y);
  private:
    UTFT *_lcd;
    int _sizex, _sizey, _offsetx, _offsety;  
};

#endif
