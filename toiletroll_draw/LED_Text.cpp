//
//

#include <Arduino.h>
#include "LED_Text.h"

LED_Text::LED_Text(LED_Strip *led)
{
    letters_init();
    _led = led;
}

LED_Text::~LED_Text(void)
{
}


// Draw a character
#define TEXTHEIGHT 7
void
LED_Text::text(int16_t x, int16_t y, const char *string, LED dotcolour)
{
    for (const char *s = string; *s != 0; s++) {
        if (letters[*s] == NULL) {
            x++;
            continue;
        }
        
        char ch[70];
        strcpy_P(ch, letters[*s]);
        byte width = strlen(ch) / TEXTHEIGHT;

        for (uint8_t i = 0; i < strlen(ch); i++) {
            LED c = _led->colour_black;
            if (ch[i] != ' ')
                c = dotcolour;          
            _led->dot(x + (i % width), y + TEXTHEIGHT - (i / width), c);
        }

        x += width;
        x++;
    }
}

uint16_t
LED_Text::text_width(const char *string)
{
    char ch[70];
    int total = 0;
    
    for (const char *s = string; *s != 0; s++) {
        if (letters[*s] == NULL) {
            total++;
            continue;
        }
        
        strcpy_P(ch, letters[*s]);
        total += strlen(ch) / TEXTHEIGHT + 1;
    }
    return total;
}

void
LED_Text::letters_init(void)
{
    static int initialized = false;

    if (initialized)
        return;
    initialized = true;
    
    letters = (const char **) malloc(sizeof(char *) * 128);
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
    	" XX"
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
    	"X "
    	"X "
    	"X "
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
