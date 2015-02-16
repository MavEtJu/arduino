#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdio.h>
#include <curses.h>

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800)
{
	pixels = (char *)malloc(sizeof(char) * n * 3);
}

void
Adafruit_NeoPixel::begin(void)
{
}

void
Adafruit_NeoPixel::initcurses(void)
{
	mainwindow = initscr();
	noecho();
	cbreak();
	nodelay(mainwindow, TRUE);
	start_color();
	use_default_colors();
	init_pair(0, COLOR_BLACK, -1);  colour[COLOR_BLACK  ] = COLOR_PAIR(0);
	init_pair(1, COLOR_RED, -1);    colour[COLOR_RED    ] = COLOR_PAIR(1);
	init_pair(2, COLOR_GREEN, -1);  colour[COLOR_GREEN  ] = COLOR_PAIR(2);
	init_pair(3, COLOR_YELLOW, -1); colour[COLOR_YELLOW ] = COLOR_PAIR(3);
	init_pair(4, COLOR_BLUE, -1);   colour[COLOR_BLUE   ] = COLOR_PAIR(4);
	init_pair(5, COLOR_MAGENTA, -1);colour[COLOR_MAGENTA] = COLOR_PAIR(5);
	init_pair(6, COLOR_CYAN, -1);   colour[COLOR_CYAN   ] = COLOR_PAIR(6);
	init_pair(7, COLOR_WHITE, -1);  colour[COLOR_WHITE  ] = COLOR_PAIR(7);

	wattrset(mainwindow, COLOR_PAIR(COLOR_WHITE));
	refresh();
	wrefresh(mainwindow);
	screen = newwin(0, 0, 0, 0);
}

void
Adafruit_NeoPixel::show(void)
{
	show2();
}

void
Adafruit_NeoPixel::show2(void)
{
	//int X = getmaxx(screen);
	//int Y = getmaxy(screen);
	int16_t x, y;
	int input;
	static byte curses_init = 0;
	int c = COLOR_BLACK;

	if (!curses_init) {
		initcurses();
		curses_init = 1;
		cbreak();
		timeout(0);
		nodelay(mainwindow, TRUE);
	}

	#define VIEW_WIDTH   17
	#define VIEW_HEIGHT  14


	wattrset(screen, colour[COLOR_WHITE]);
	werase(screen);
	curs_set(0);
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, 0, VIEW_WIDTH + 1, "+");
	mvwprintw(screen, VIEW_HEIGHT + 1, 0, "+");
	mvwprintw(screen, VIEW_HEIGHT + 1, VIEW_WIDTH + 1, "+");
	for (x = 0; x < VIEW_WIDTH; x++) {
		mvwprintw(screen, 0, 1 + x, "-");
		mvwprintw(screen, VIEW_HEIGHT + 1, 1 + x, "-");
	}
	for (y = 0; y < VIEW_HEIGHT; y++) {
		mvwprintw(screen, 1 + y, 0, "|");
		mvwprintw(screen, 1 + y, VIEW_WIDTH + 1, "|");
	}

	c = COLOR_BLACK;
	for (y = VIEW_HEIGHT - 1; y >= 0; y--) {
		for (x = 0; x < VIEW_WIDTH; x++) {

			uint8_t r = pixels[3 * (y * VIEW_WIDTH + x)];
			uint8_t g = pixels[3 * (y * VIEW_WIDTH + x) + 1];
			uint8_t b = pixels[3 * (y * VIEW_WIDTH + x) + 2];

			if (r == 0) {
				if (g == 0) {
					if (b == 0) {
						c = COLOR_BLACK;
					} else {
						c = COLOR_BLUE;
					}
				} else {
					if (b == 0) {
						c = COLOR_GREEN;
					} else {
						c = COLOR_CYAN;
					}
				}
			} else {
				if (g == 0) {
					if (b == 0) {
						c = COLOR_RED;
					} else {
						c = COLOR_MAGENTA;
					}
				} else {
					if (b == 0) {
						c = COLOR_YELLOW;
					} else {
						c = COLOR_WHITE;
					}
				}
			}

			wattrset(screen, colour[c]);
			if (c == COLOR_BLACK)
				mvwprintw(screen, VIEW_HEIGHT - y, 1 + x, " ");
			else
				mvwprintw(screen, VIEW_HEIGHT - y, 1 + x, "X");
		}
	}

	wattrset(screen, colour[COLOR_WHITE]);
	int linenr = Serial.lines();
	y = VIEW_HEIGHT + 3;
	while (linenr != 1) {
		mvwprintw(screen, y++, 1, Serial.get());
		linenr--;
	}
	Serial.clear();

	wattrset(screen, colour[COLOR_WHITE]);
	wrefresh(screen);

	if ((input = wgetch(mainwindow)) == ERR)
		return;
	if (input == 'q' || input == 'Q') {
		endwin();
		exit(0);
	}
}

void
Adafruit_NeoPixel::show1(void)
{
	#define VIEW_WIDTH   17
	#define VIEW_HEIGHT  14
	int16_t x, y;

	printf("\033[H");
	printf("+");
	for (x = 0; x < VIEW_WIDTH; x++) {
		printf("-");
	}
	printf("+\n");

	for (y = VIEW_HEIGHT - 1; y >= 0; y--) {
		printf("|");
		for (x = 0; x < VIEW_WIDTH; x++) {
			if (pixels[3 * (y * VIEW_WIDTH + x)] == 0 
			 && pixels[3 * (y * VIEW_WIDTH + x) + 1] == 0 
			 && pixels[3 * (y * VIEW_WIDTH + x) + 2] == 0) {
			    printf(" ");
			} else {
			    printf("X");
			}
		}
		printf("|\n");
	}

	printf("+");
	for (x = 0; x < VIEW_WIDTH; x++) {
		printf("-");
	}
	printf("+");
}
