//
//

#include <Arduino.h>
#include <pgmspace.h>
#include <Adafruit_NeoPixel.h>
#include "led_tools.h"

LED::LED(uint16_t amount, uint8_t pin) : Adafruit_NeoPixel(amount, pin, NEO_GRB + NEO_KHZ800)
{
    _colourlast = this->Color(0, 0, 0);
    colour_red = Color(8, 0, 0);
    colour_green = Color(0, 8, 0);
    colour_blue = Color(0, 0, 8);
    colour_black = Color(0, 0, 0);
    colour_white = Color(8, 8, 8);
    colour_purple = Color(8, 0, 8);
    colour_cyan = Color(0, 8, 8);
    colour_yellow = Color(8, 8, 0);
    _strip = (uint32_t *)malloc(amount * sizeof(uint32_t));
    letters_init();
}

void
LED::start(void)
{
    this->begin();
    this->show();
}

// Set the size of the view
void
LED::view(uint16_t xmax, uint16_t ymax)
{
    _xmax = xmax;
    _ymax = ymax;
    _matrix = (uint32_t **)malloc(sizeof(uint32_t *) * ymax);
    for (uint16_t y = 0; y < _ymax; y++) {
        _matrix[y] = _strip + y * _xmax;
    }
}

// 
void
LED::display(void)
{
    for (uint16_t o = 0; o < _xmax * _ymax; o++) {
        setPixelColor(o, _strip[o]);
    }
    show();
}

// Clear everything
void
LED::clear(void)
{
    clear(led.colour_black);
}

void
LED::clear(uint32_t colour)
{
    for (uint16_t x = 0; x < _xmax * _ymax; x++) {
        _strip[x] = colour;
    }
}


// Set the current colour
void
LED::colour_set(uint32_t colour)
{
    _colourlast = colour;
}

uint32_t
LED::colour_random(void)
{
    switch (rand() % 8) {
        case 0: return colour_white;
        case 1: return colour_black;
        case 2: return colour_red;
        case 3: return colour_green;
        case 4: return colour_blue;
        case 5: return colour_cyan;
        case 6: return colour_purple;
        case 7: return colour_yellow;
        default:
            return colour_white;
    }
}


// Colour the LEDs in the strip from offset 1 to offset 2
void
LED::strip_o1_o2(uint16_t o1, uint16_t o2)
{
    for (uint16_t o = o1; o <= o2; o++) {
        _strip[o] = _colourlast;
    }
}
void
LED::strip_o1_o2(uint16_t o1, uint16_t o2, uint32_t colour)
{
    _colourlast = colour;
    strip_o1_o2(o1, o2);
}

// Colour the LEDs in the strip from offset to offset + length
void
LED::strip_o_length(uint16_t o, uint16_t length)
{
    for (uint16_t x = o; x < o + length; x++) {
        _strip[x] = _colourlast;
    }
}
void
LED::strip_o_length(uint16_t o, uint16_t length, uint32_t colour)
{
    _colourlast = colour;
    strip_o_length(o, length);
}

// Plot a dot
void
LED::dot(int16_t x, int16_t y)
{
    if (x < 0 || x >= _xmax)
        return;
    if (y < 0 || y >= _ymax)
        return;
    _matrix[y][x] = _colourlast;
}

void
LED::dot(int16_t x, int16_t y, uint32_t colour)
{
    _colourlast = colour;
    dot(x, y);
}

// Colour the LEDs in the matrix from (x1, y1) x (x2, y2)
void
LED::square(int16_t xo, int16_t yo, uint16_t dx, uint16_t dy)
{
    for (int16_t x = 0; x < dx; x++) {
        if (xo + x < 0 || xo + x >= _xmax)
            continue;
        for (int16_t y = 0; y < dy; y++) {
            if (yo + y < 0 || yo + y >= _ymax)
                continue;
            _matrix[yo + y][xo + x] = _colourlast;
        }
    }
}

void
LED::square(int16_t xo, int16_t yo, uint16_t dx, uint16_t dy, uint32_t colour)
{
    _colourlast = colour;
    square(xo, yo, dx, dy);
}

// Draw a line
// http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm_for_integer_arithmetic
// http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
void
LED::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    int w = x2 - x1;
    int h = y2 - y1;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if (w < 0)
        dx1 = -1;
    else if (w > 0)
            dx1 = 1;
    if (h < 0)
        dy1 = -1;
    else if (h > 0)
        dy1 = 1;
    if (w < 0)
        dx2 = -1;
    else if (w > 0)
        dx2 = 1;
        
    int longest = abs(w);
    int shortest = abs(h);
    if (!(longest > shortest)) {
        longest = abs(h);
        shortest = abs(w);
        if (h < 0)
            dy2 = -1;
        else if (h > 0)
            dy2 = 1;
        dx2 = 0;
    }
    
    int numerator = longest >> 1;
    for (int i = 0; i <= longest; i++) {
        dot(x1, y1);
        numerator += shortest;
        if (!(numerator < longest)) {
            numerator -= longest;
            x1 += dx1;
            y1 += dy1;
        } else {
            x1 += dx2;
            y1 += dy2;
        }
    }
}

void
LED::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t colour)
{
    _colourlast = colour;
    line(x1, y1, x2, y2);
}

// Draw a character
#define TEXTHEIGHT 7
void
LED::text(int16_t x, int16_t y, char *string)
{
    dot(x, y);
    uint32_t dotcolour = _colourlast;
    
    for (char *s = string; *s != 0; s++) {
        if (letters[*s] == NULL) {
            x++;
            continue;
        }
        
        char ch[70];
        strcpy_P(ch, letters[*s]);
        byte width = strlen(ch) / TEXTHEIGHT;

        for (uint8_t i = 0; i < strlen(ch); i++) {
            uint32_t c = colour_black;
            if (ch[i] != ' ')
                c = dotcolour;          
            dot(x + (i % width), y + (i / width), c);
        }

//        Serial.print("char: '");
//        Serial.print(*s);
//        Serial.print("' width: ");
//        Serial.print(width);
//        Serial.println("");
        x += width;
        x++;
    }
}

void
LED::text(int16_t x, int16_t y, char *string, uint32_t colour)
{
    _colourlast = colour;
    text(x, y, string);
}

uint16_t
LED::text_width(char *string)
{
    char ch[70];
    int total = 0;
    
    for (char *s = string; *s != 0; s++) {
        if (letters[*s] == NULL) {
            total++;
            continue;
        }
        
        strcpy_P(ch, letters[*s]);
        total += strlen(ch) / TEXTHEIGHT;
    }
    return total;
}

void
LED::letters_init(void)
{
    static int initialized = false;

    if (initialized)
        return;
    initialized = true;
    
    letters = (char **) malloc(sizeof(char *) * 128);
    for (int c = 0; c < 128; c++) {
        letters[c] = NULL;
    }
    letters['A'] = PSTR( 
    	" XXX "
    	"X   X"
    	"X   X"
    	"X   X"
    	"XXXXX"
    	"X   X"
    	"X   X");
    letters['B'] = PSTR( 
    	"XXXX "
    	"X   X"
    	"X   X"
    	"XXXX "
    	"X   X"
    	"X   X"
    	"XXXX ");
    letters['C'] = PSTR( 
    	" XXX "
    	"X   X"
    	"X    "
    	"X    "
    	"X    "
    	"X   X"
    	" XXX ");
    letters['D'] = PSTR( 
    	"XXXX "
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	"XXXX ");
    letters['E'] = PSTR( 
    	"XXXXX"
    	"X    "
    	"X    "
    	"XXXX "
    	"X    "
    	"X    "
    	"XXXXX");
    letters['F'] = PSTR( 
    	"XXXXX"
    	"X    "
    	"X    "
    	"XXXX "
    	"X    "
    	"X    "
    	"X    ");
    letters['G'] = PSTR( 
    	" XXX "
    	"X   X"
    	"X    "
    	"X XXX"
    	"X   X"
    	"X   X"
    	" XXXX");
    letters['H'] = PSTR( 
    	"X   X"
    	"X   X"
    	"X   X"
    	"XXXXX"
    	"X   X"
    	"X   X"
    	"X   X");
    letters['I'] = PSTR( 
    	"XXX"
    	" X "
    	" X "
    	" X "
    	" X "
    	" X "
    	"XXX");
    letters['J'] = PSTR( 
    	"    X"
    	"    X"
    	"    X"
    	"    X"
    	"    X"
    	"X   X"
    	"XXXXX");
    letters['K'] = PSTR( 
    	"X   X"
    	"X  X "
    	"X X  "
    	"XX   "
    	"X X  "
    	"X  X "
    	"X   X");
    letters['L'] = PSTR( 
    	"X    "
    	"X    "
    	"X    "
    	"X    "
    	"X    "
    	"X    "
    	"XXXXX");
    letters['M'] = PSTR( 
    	"X     X"
    	"XX   XX"
    	"X X X X"
    	"X  X  X"
    	"X     X"
    	"X     X"
    	"X     X");
    letters['N'] = PSTR( 
    	"X   X"
    	"XX  X"
    	"XX  X"
    	"X X X"
    	"X X X"
    	"X  XX"
    	"X  XX");
    letters['O'] = PSTR( 
    	" XXX "
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	" XXX ");
    letters['P'] = PSTR( 
    	"XXXX "
    	"X   X"
    	"X   X"
    	"XXXX "
    	"X    "
    	"X    "
    	"X    ");
    letters['Q'] = PSTR( 
    	" XXX "
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	"X  XX"
    	" XXXX");
    letters['R'] = PSTR( 
    	"XXXX "
    	"X   X"
    	"X   X"
    	"XXXX "
    	"X   X"
    	"X   X"
    	"X   X");
    letters['S'] = PSTR( 
    	" XXX "
    	"X    "
    	"X    "
    	" XXX "
    	"    X"
    	"    X"
    	"XXXX ");
    letters['T'] = PSTR( 
    	"XXXXX"
    	"  X  "
    	"  X  "
    	"  X  "
    	"  X  "
    	"  X  "
    	"  X  ");
    letters['U'] = PSTR( 
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	" XXX ");
    letters['V'] = PSTR( 
    	"X   X"
    	"X   X"
    	"X   X"
    	"X   X"
    	" X X "
    	" X X "
    	"  X  ");
    letters['W'] = PSTR( 
    	"X     X"
    	"X     X"
    	"X     X"
    	"X  X  X"
    	"X X X X"
    	"XX   XX"
    	"X     X");
    letters['X'] = PSTR( 
    	"X   X"
    	"X   X"
    	" X X "
    	"  X  "
    	" X X "
    	"X   X"
    	"X   X");
    letters['Y'] = PSTR( 
    	"X   X"
    	"X   X"
    	"X   X"
    	" XXX "
    	"  X  "
    	"  X  "
    	"  X  ");
    letters['Z'] = PSTR( 
    	"XXXXX"
    	"    X"
    	"   X "
    	"  X  "
    	" X   "
    	"X    "
    	"XXXXX");
    
    letters['a'] = PSTR(
    	"    "
    	"    "
    	" XX "
    	"   X"
    	" XXX"
    	"X  X"
    	" XXX");
    letters['b'] = PSTR(
    	"X   "
    	"X   "
    	"XXX "
    	"X  X"
    	"X  X"
    	"X  X"
    	"XXX ");
    letters['c'] = PSTR(
    	"    "
    	"    "
    	" XXX"
    	"X   "
    	"X   "
    	"X   "
    	" XXX");
    letters['d'] = PSTR(
    	"   X"
    	"   X"
    	" XXX"
    	"X  X"
    	"X  X"
    	"X  X"
    	" XXX");
    letters['e'] = PSTR(
    	"    "
    	"    "
    	" XX "
    	"X  X"
    	"XXXX"
    	"X   "
    	" XXX");
    letters['f'] = PSTR(
    	" XX"
    	"X  "
    	"X  "
    	"XXX"
    	"X  "
    	"X  "
    	"X  ");
    letters['g'] = PSTR(
    	" XX "
    	"X  X"
    	" XX "
    	"X   "
    	" XX "
    	"X  X"
    	" XX ");
    letters['h'] = PSTR(
    	"X   "
    	"X   "
    	"XXX "
    	"X  X"
    	"X  X"
    	"X  X"
    	"X  X");
    letters['i'] = PSTR(
    	"X"
    	" "
    	"X"
    	"X"
    	"X"
    	"X"
    	"X");
    letters['j'] = PSTR(
    	"  X"
    	"   "
    	" XX "
    	"  X"
    	"  X"
    	"  X"
    	"XX ");
    letters['k'] = PSTR(
    	"X   "
    	"X   "
    	"X  X"
    	"X X "
    	"XX  "
    	"X X "
    	"X  X");
    letters['l'] = PSTR(
    	"X"
    	"X"
    	"X"
    	"X"
    	"X"
    	"X"
    	"X");
    letters['m'] = PSTR(
    	"       "
    	"       "
    	"XXX XX "
    	"X  X  X"
    	"X  X  X"
    	"X  X  X"
    	"X  X  X");
    letters['n'] = PSTR(
    	"    "
    	"    "
    	"XXX "
    	"X  X"
    	"X  X"
    	"X  X"
    	"X  X");
    letters['o'] = PSTR(
    	"    "
    	"    "
    	" XX "
    	"X  X"
    	"X  X"
    	"X  X"
    	" XX ");
    letters['p'] = PSTR(
    	"    "
    	"    "
    	"XXX "
    	"X  X"
    	"XXX "
    	"X   "
    	"X   ");
    letters['q'] = PSTR(
    	"    "
    	"    "
    	" XXX"
    	"X  X"
    	" XXX"
    	"   X"
    	"   X");
    letters['r'] = PSTR(
    	"    "
    	"    "
    	"X XX"
    	"XX  "
    	"X   "
    	"X   "
    	"X   ");
    letters['s'] = PSTR(
    	"    "
    	"    "
    	" XX "
    	"X   "
    	" XX "
    	"   X"
    	"XXX ");
    letters['t'] = PSTR(
    	"   "
    	" X "
    	"XXX"
    	" X "
    	" X "
    	" X "
    	" X ");
    letters['u'] = PSTR(
    	"    "
    	"    "
    	"X  X"
    	"X  X"
    	"X  X"
    	"X  X"
    	" XXX");
    letters['v'] = PSTR(
    	"    "
    	"    "
    	"X  X"
    	"X  X"
    	"X  X"
    	" XX "
    	" XX ");
    letters['w'] = PSTR(
    	"       "
    	"       "
    	"X  X  X"
    	"X  X  X"
    	"X  X  X"
    	"X  X  X"
    	"XXXXXX ");
    letters['x'] = PSTR(
    	"    "
    	"    "
    	"X  X"
    	"X  X"
    	" XX "
    	"X  X"
    	"X  X");
    letters['y'] = PSTR(
    	"    "
    	"X  X"
    	"X  X"
    	" XXX"
    	"   X"
    	"   X"
    	" XX ");
    letters['z'] = PSTR(
    	"    "
    	"    "
    	"XXXX"
    	"   X"
    	" XX "
    	"X   "
    	"XXXX");
    
    letters[' '] = PSTR(
    	"  "
    	"  "
    	"  "
    	"  "
    	"  "
    	"  "
    	"  ");
    
    letters['0'] = PSTR(
    	" XXX "
    	"X   X"
    	"X  XX"
    	"X X X"
    	"XX  X"
    	"X   X"
    	" XXX ");
    letters['1'] = PSTR(
    	" X "
    	"XX "
    	" X "
    	" X "
    	" X "
    	" X "
    	"XXX");
    letters['2'] = PSTR(
    	" XXX "
    	"X   X"
    	"    X"
    	"   X "
    	" XX  "
    	"X    "
    	"XXXXX");
    letters['3'] = PSTR(
    	"XXXX "
    	"    X"
    	"    X"
    	" XXX "
    	"    X"
    	"    X"
    	"XXXX ");
    letters['4'] = PSTR(
    	"X   X"
    	"X   X"
    	"X   X"
    	"XXXXX"
    	"    X"
    	"    X"
    	"    X");
    letters['5'] = PSTR(
    	"XXXX "
    	"X    "
    	"X    "
    	"XXXX "
    	"    X"
    	"    X"
    	"XXXX ");
    letters['6'] = PSTR(
    	" XXX "
    	"X    "
    	"XXXX "
    	"X   X"
    	"X   X"
    	"X   X"
    	" XXX ");
    letters['7'] = PSTR(
    	"XXXXX"
    	"    X"
    	"    X"
    	"   X "
    	"   X "
    	"  X  "
    	"  X  ");
    letters['8'] = PSTR(
    	" XXX "
    	"X   X"
    	"X   X"
    	" XXX "
    	"X   X"
    	"X   X"
    	" XXX ");
    letters['9'] = PSTR(
    	" XXX "
    	"X   X"
    	"X   X"
    	"X   X"
    	" XXXX"
    	"    X"
    	" XXX ");
    
    letters['~'] = PSTR(
    	"      "
    	"      "
    	" XX  X"
    	"X  XX "
    	"      "
    	"      "
    	"      ");
    letters['`'] = PSTR(
    	"X "
    	" X"
    	"  "
    	"  "
    	"  "
    	"  "
    	"  ");
    letters['!'] = PSTR(
    	"X"
    	"X"
    	"X"
    	"X"
    	"X"
    	" "
    	"X");
    letters['@'] = PSTR(
    	" XXX "
    	"X   X"
    	"X XXX"
    	"X X X"
    	"X XXX"
    	"X    "
    	" XXXX");
    letters['#'] = PSTR(
    	"     "
    	" X X "
    	"XXXXX"
    	" X X "
    	"XXXXX"
    	" X X "
    	"     ");
    letters['$'] = PSTR(
    	"  X  "
    	" XXX "
    	"X X  "
    	" XXX "
    	"  X X"
    	" XXX "
    	"  X  ");
    letters['%'] = PSTR(
    	" X   X "
    	"X X  X "
    	" X  X  "
    	"   X   "
    	"  X  X "
    	" X  X X"
    	" X   X ");
    letters['^'] = PSTR(
    	" XX "
    	"X  X"
    	"    "
    	"    "
    	"    "
    	"    "
    	"    ");
    letters['&'] = PSTR(
    	"  XX  "
    	" X  X "
    	"  XX  "
    	" XX   "
    	"X  X X"
    	"X   X "
    	" XXX X");
    letters['('] = PSTR(
    	"  X"
    	" X "
    	"X  "
    	"X  "
    	"X  "
    	" X "
    	"  X");
    letters[')'] = PSTR(
    	"X  "
    	" X "
    	"  X"
    	"  X"
    	"  X"
    	" X "
    	"X  ");
    letters['-'] = PSTR(
    	"    "
    	"    "
    	"    "
    	"XXXX"
    	"    "
    	"    "
    	"    ");
    letters['='] = PSTR(
    	"    "
    	"    "
    	"XXXX"
    	"    "
    	"XXXX"
    	"    "
    	"    ");
    letters['_'] = PSTR(
    	"    "
    	"    "
    	"    "
    	"    "
    	"    "
    	"XXXX"
    	"    ");
    letters['+'] = PSTR(
    	"     "
    	"  X  "
    	"  X  "
    	"XXXXX"
    	"  X  "
    	"  X  "
    	"     ");
    letters['['] = PSTR(
    	"XX"
    	"X "
    	"X  "
    	"X  "
    	"X  "
    	"X "
    	"XX");
    letters[']'] = PSTR(
    	"XX"
    	" X"
    	" X"
    	" X"
    	" X"
    	" X"
    	"XX");
    letters['{'] = PSTR(
    	"  X"
    	" X "
    	" X "
    	"X  "
    	" X "
    	" X "
    	"  X");
    letters['}'] = PSTR(
    	"X  "
    	" X "
    	" X "
    	"  X"
    	" X "
    	" X "
    	"X  ");
    letters['\\'] = PSTR(
    	"X    "
    	"X    "
    	" X   "
    	"  X  "
    	"   X "
    	"    X"
    	"    X");
    letters['|'] = PSTR(
    	"X"
    	"X"
    	"X"
    	"X"
    	"X"
    	"X"
    	"X");
}


