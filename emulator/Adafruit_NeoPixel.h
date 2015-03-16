//

#if !defined Adafruit_NeoPixel__h
#define Adafruit_NeoPixel__h

#include <curses.h>

#define NEO_GRB		(1 << 0)
#define	NEO_KHZ800	(1 << 1)

class Adafruit_NeoPixel {
    public:
	Adafruit_NeoPixel(uint16_t num, uint8_t pin, uint8_t options);
	char *pixels;
	void begin(void);
	void show(void);
	#ifdef SIMULATOR
	void setsize(uint16_t w, uint16_t h);
	#endif

    private:
	WINDOW *mainwindow;
	WINDOW *screenLED;
	WINDOW *screenSerial;
	uint16_t VIEW_HEIGHT, VIEW_WIDTH;
	uint8_t type;

	void show1(void);
	void show2(void);
	void initcurses(void);
};

#endif
