#include <Arduino.h>
#include "LED_Strip.h"
#include "A_Tools.h"
#include "slides.h"


MYCONSTRUCTOR_SLIDESHOW(LED_mario1)
{
    /*
     * . black
     * W white
     * R red
     * G green
     * B blue
     * y yellow
     * r brown
     * m magenta
     *
     * S skin
     * B brown
     */
    set_imgs(2);

    add_image(13, 624, PSTR(
	/*
        "     RRRRRR     "
        "    RRRRRRRRRR  "
        "    rrrSSS.S    "
        "   rSrSSSS.SSS  "
        "   rSrSSSSS.SSS "
        "   rrSSSSS....  "
        "     SSSSSSSS   "
        "    RRBRRRB     "
        "   RRRBRRBRRR   "
        "  RRRRBBBBRRRR  "
        "  SSRByBByBRSS  "
        "  SSSBBBBBBSSS  "
        "  SSBBBBBBBBSS  "
        "    BBB  BBB    "
        "   ....  ....   "
        "  .....  .....  "
	*/
	"\x07\x20\x2e\x42\x52\x53\x72\x79\x00\xb6\x6d\x03\x00\x60\xdb\xb6\x6d\x03\xd0\x96\x64\x08\x00\x65\x49\x32\x24\x81\xb2\x24\xc9\x90\x44\x4b\x92\x4c\x12\x00\x20\x49\x92\x04\x80\x4d\xdb\x04\x00\xd8\xa6\x4d\xdb\x80\x6d\x93\xa4\x6d\x03\x39\x59\xb2\x46\x82\xa4\x24\x49\x24\x41\x4a\x92\x24\x91\x00\x24\x01\x92\x00\x20\x49\x80\x24\x01\x92\x24\x40\x92\x04"
	));
    /*
     * R red
     * W white
     * B black
     */
    add_image(16, 512, PSTR(
	/*
        "     ......     "
        "   ..RRRRWW..   "
        "  .WWRRRRWWWW.  "
        " .WWRRRRRRWWWW. "
        " .WWRWWWWRRWWW. "
        ".RRRWWWWWWRRRRR."
        ".RRRWWWWWWRRWWR."
        ".WRRWWWWWWRWWWW."
        ".WWRRWWWWRRWWWW."
        ".WWRRRRRRRRRWWR."
        ".WRR........RRR."
        " ...WW.WW.WW... "
        "  .WWW.WW.WWW.  "
        "  .WWWWWWWWWW.  "
        "   ..WWWWWW..   "
        "     ......     "
	*/
	"\x04\x20\x2e\x52\x57\x00\x54\x15\x00\x40\xa9\x7e\x01\xd0\xab\xfe\x07\xf4\xaa\xfa\x1f\xf4\xfe\xeb\x1f\xa9\xff\xaf\x6a\xa9\xff\xaf\x6f\xad\xff\xef\x7f\xbd\xfe\xeb\x7f\xbd\xaa\xaa\x6f\xad\x55\x55\x6a\x54\xdf\xf7\x15\xd0\xdf\xf7\x07\xd0\xff\xff\x07\x40\xfd\x7f\x01\x00\x54\x15\x00"
	));

    add_colourmap('S', 208 >> 4, 189 >> 4, 156 >> 4);
}

// =======================

MYCONSTRUCTOR_SLIDESHOW(LED_galaga1)
{
    /*
     * R red
     * W white
     * B blue
     *
     * http://kandipatterns.com/patterns/misc/galaga-ship-5207
     *
     */
    set_imgs(3);
    add_image(15, 480, PSTR(
	/*
        "       W        "
        "       W        "
        "       W        "
        "      WWW       "
        "      WWW       "
        "      WWW       "
        "   R  WWW  R    "
        "   R WWWWW R    "
        "R  WBWWRWWBW  R "
        "R  BWWRRRWWB  R "
        "W  WWWRWRWWW  W "
        "W WWWWWWWWWWW W "
        "WWWWWRWWWRWWWWW "
        "WWW RRWWWRR WWW "
        "WW  RR W RR  WW "
        "W      W      W "
	*/
	"\x04\x20\x42\x52\x57\x00\xc0\x00\x00\x00\x30\x00\x00\x00\x0c\x00\x00\xc0\x0f\x00\x00\xf0\x03\x00\x00\xfc\x00\x00\x08\x3f\x08\x00\xf2\x3f\x02\xc2\xbd\xdf\xa0\xd0\xab\x1f\x38\xfc\xee\x0f\xcf\xff\xff\xcf\xff\xfb\xfb\xff\x8f\xfe\xca\xff\xa0\x8c\xc2\x0f\x00\x03\xc0"
	));

    /*
     * From http://fc03.deviantart.net/fs50/f/2009/271/8/f/Galaga_Sprites_by_mammaDX.png
     */
    add_image(13, 260, PSTR(
	/*
        "                "
        "                "
        " BB   y   BB    "
        "  BByRyRyBB     "
        "   BRRyRRB      "
        "    yyyyy       "
        "    ByyyB       "
        "  BBBRRRBBB     "
        " BBB RRR BBB    "
        "BBBB yyy BBBB   "
        "BBB  RRR  BBB   "
        "BBB   R   BBB   "
        "                "
        "                "
        "                "
        "                "
	*/
	"\x04\x20\x42\x52\x79\x14\x30\x50\x40\xed\x5e\x00\xa4\x6b\x00\xc0\xff\x00\x00\xfd\x01\x40\xa5\x56\x40\x85\x4a\x45\x15\x3f\x55\x15\xa8\x50\x55\x80\x40\x05"
	));

    add_image(15, 480, PSTR(
	/*
        "      G G       "
        "      G G       "
        "   GGRRGRRGG    "
        "    GRRGRRG     "
        "     GGGGG      "
        "    GyyGyyG     "
        "  GGGyyyyyGGG   "
        "GGGGGyyyyyGGGG  "
        " GGGGyyyyyGGG   "
        " GRGG R R GGRG  "
        "GGRG  R R  GRGG "
        "GRGG       GGRG "
        "GRRG       GRRG "
        "GRRG       GRRG "
        "GGGG       GGGG "
        " GG         GG  "
	*/
	"\x04\x20\x47\x52\x79\x00\x10\x01\x00\x00\x44\x00\x00\x94\xa6\x05\x00\xa4\x69\x00\x00\x54\x05\x00\x40\xdf\x07\x00\xd5\xff\x15\x54\xf5\x7f\x15\x54\xfd\x5f\x01\x59\x88\x94\x51\x06\x22\x64\x65\x01\x00\x65\x69\x00\x40\x5a\x1a\x00\x90\x56\x05\x00\x54\x51\x00\x00\x14"
	));
}

// =================================

void
LED_minecraft1::create_colourmap(void)
{
    memset(&colourmap, 0, sizeof(colourmap));

    clear_colourmap();
    add_colourmap(' ',   0 >> 3,   0 >> 3,   0 >> 3);

    // Tools (sword, pickaxe, shovel, axe)
    add_colourmap('0', 137 >> 3, 103 >> 3,  39 >> 3);
    add_colourmap('1', 104 >> 3,  78 >> 3,  30 >> 3);
    add_colourmap('2',  73 >> 3,  54 >> 3,  21 >> 3);
    add_colourmap('3',  40 >> 3,  30 >> 3,  11 >> 3);
    add_colourmap('4', 255 >> 3, 255 >> 3, 255 >> 3);
    add_colourmap('5', 216 >> 3, 216 >> 3, 216 >> 3);
    add_colourmap('6', 150 >> 3, 150 >> 3, 150 >> 3);
    add_colourmap('7', 107 >> 3, 107 >> 3, 107 >> 3);
    add_colourmap('8',  68 >> 3,  68 >> 3,  68 >> 3);
    add_colourmap('9',  40 >> 3,  40 >> 3,  40 >> 3);
    
    // Buckets
    add_colourmap('a',  53 >> 4,  53 >> 4,  53 >> 4);
    add_colourmap('b',  81 >> 4,  81 >> 4,  81 >> 4);
    add_colourmap('c', 114 >> 4, 114 >> 4, 114 >> 4);
    add_colourmap('d', 150 >> 4, 150 >> 4, 150 >> 4);
    add_colourmap('e', 168 >> 4, 168 >> 4, 168 >> 4);
    add_colourmap('f', 216 >> 4, 216 >> 4, 216 >> 4);
    add_colourmap('g', 255 >> 4, 255 >> 4, 255 >> 4);
    add_colourmap('h',  71 >> 4, 114 >> 4, 236 >> 4);
    add_colourmap('i',  58 >> 4, 101 >> 4, 223 >> 4);
    add_colourmap('j',  52 >> 4,  95 >> 4, 218 >> 4);
    add_colourmap('k',  50 >> 4,  93 >> 4, 215 >> 4);
    add_colourmap('l',  45 >> 4,  89 >> 4, 211 >> 4);
    add_colourmap('m',  63 >> 4,  87 >> 4, 154 >> 4);
    add_colourmap('n',  75 >> 4, 100 >> 4, 167 >> 4);
    add_colourmap('o',  82 >> 4, 105 >> 4, 174 >> 4);
    add_colourmap('p', 100 >> 4, 124 >> 4, 191 >> 4);
    add_colourmap('q', 255 >> 4,   2 >> 4,   0 >> 4);
    add_colourmap('r', 247 >> 4, 150 >> 4,  37 >> 4);
    add_colourmap('s', 255 >> 4, 210 >> 4,   4 >> 4);
}

MYCONSTRUCTOR_SLIDESHOW(LED_minecraft1)
{
    create_colourmap();
    set_imgs(6);

    /* From http://fc04.deviantart.net/fs71/f/2013/162/9/5/minecraft_sword_patterns_by_sarrel-d68p8xf.png */
    add_image(16, 1024, PSTR(
	/*
        "             888"
        "            8458"
        "           84548"
        "          84548 "
        "         84548  "
        "        84548   "
        "  100   84548    "
        "  979 84548     "
        "   9694548      "
        "   969548       "
        "    9699        "
        "   219669       "
        "  203 9979      "
        "9913            "
        "969             "
        "999             "
	*/
	"\x0b\x20\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x00\x00\x00\x00\x00\x00\x90\x99\x00\x00\x00\x00\x00\x00\x59\x96\x00\x00\x00\x00\x00\x90\x65\x95\x00\x00\x00\x00\x00\x59\x56\x09\x00\x00\x00\x00\x90\x65\x95\x00\x00\x00\x00\x00\x59\x56\x09\x00\x00\xaa\x00\x90\x65\x95\x00\x00\x00\x8a\x0a\x59\x56\x09\x00\x00\x00\xa0\xa7\x65\x95\x00\x00\x00\x00\xa0\xa7\x56\x09\x00\x00\x00\x00\x00\x7a\xaa\x00\x00\x00\x00\x00\x30\xa2\x77\x0a\x00\x00\x00\x00\x13\x04\xaa\xa8\x00\x00\x00\xaa\x42\x00\x00\x00\x00\x00\x00\x7a\x0a\x00\x00\x00\x00\x00\x00\xaa\x0a\x00\x00\x00\x00\x00\x00"
	));

    /* http://fc04.deviantart.net/fs71/f/2013/162/9/8/minecraft_pickaxe_patterns_by_sarrel-d68p8h7.png */
    add_image(13, 676, PSTR(
	/*
        "                "
        "                "
        "     88888      "
        "    845665821   "
        "     88886603   "
        "         2568   "
        "        213658  "
        "       203 868  "
        "      213  868  "
        "     203   858  "
        "    213    848  "
        "   203      8   "
        "  213           "
        " 203            "
        " 13             "
        "                "
	*/
	"\x09\x20\x30\x31\x32\x33\x34\x35\x36\x38\x00\x00\x88\x88\x08\x00\x00\x00\x58\x76\x67\x38\x02\x00\x00\x88\x88\x77\x41\x00\x00\x00\x00\x30\x76\x08\x00\x00\x00\x30\x42\x67\x08\x00\x00\x30\x41\x80\x87\x00\x00\x30\x42\x00\x78\x08\x00\x30\x41\x00\x80\x86\x00\x30\x42\x00\x00\x58\x08\x30\x41\x00\x00\x00\x08\x30\x42\x00\x00\x00\x00\x30\x41\x00\x00\x00\x00\x00\x42\x00\x00\x00\x00\x00\x00"
	));

    /* http://fc06.deviantart.net/fs70/f/2013/162/8/5/minecraft_axe_patterns_by_sarrel-d68p7v3.png */
    add_image(12, 672, PSTR(
	/*
        "                "
        "         88     "
        "        8448    "
        "       84658    "
        "      8466621   "
        "      8456763   "
        "       8826768  "
        "        203668  "
        "       213 88   "
        "      203       "
        "     213        "
        "    203         "
        "   213          "
        "  203           "
        "  13            "
        "                "
	*/
	"\x0a\x20\x30\x31\x32\x33\x34\x35\x36\x37\x38\x00\x00\x00\x90\x09\x00\x00\x00\x00\x59\x95\x00\x00\x00\x90\x75\x96\x00\x00\x00\x59\x77\x37\x02\x00\x00\x59\x76\x78\x04\x00\x00\x90\x39\x87\x97\x00\x00\x00\x13\x74\x97\x00\x00\x30\x42\x90\x09\x00\x00\x13\x04\x00\x00\x00\x30\x42\x00\x00\x00\x00\x13\x04\x00\x00\x00\x30\x42\x00\x00\x00\x00\x13\x04\x00\x00\x00\x00\x42\x00\x00\x00\x00\x00"
	));

    /* http://fc07.deviantart.net/fs70/f/2013/162/e/1/minecraft_shovel_patterns_by_sarrel-d68p8pl.png */
    add_image(13, 676, PSTR(
	/*
        "                "
        "                "
        "          888   "
        "         84468  "
        "        845648  "
        "       8456548  "
        "        26548   "
        "       20348    "
        "      203 8     "
        "     213        "
        "    203         "
        "   213          "
        " 3203           "
        " 213            "
        "  23            "
        "                "
	*/
	"\x09\x20\x30\x31\x32\x33\x34\x35\x36\x38\x00\x00\x00\x00\x80\x88\x00\x00\x00\x00\x80\x55\x87\x00\x00\x00\x80\x65\x57\x08\x00\x00\x80\x65\x67\x85\x00\x00\x00\x30\x67\x85\x00\x00\x00\x30\x41\x85\x00\x00\x00\x30\x41\x80\x00\x00\x00\x30\x42\x00\x00\x00\x00\x30\x41\x00\x00\x00\x00\x30\x42\x00\x00\x00\x00\x34\x41\x00\x00\x00\x00\x30\x42\x00\x00\x00\x00\x00\x30\x04\x00\x00\x00\x00\x00"
	));

    /* Water and lava bucket */

    add_image(12, 780, PSTR(
	/*
        "                "
        "                "
        "     aaabbb     "
        "   aanoooopbb   "
        "  ammkjjjjippa  "
        "  balkkjjjiiaa  "
        "  bfaakjjjaaca  "
        "  bfffaaaaiica  "
        "  bffgheeeidca  "
        "   bfgfeeeica   "
        "   bffgfeddca   "
        "   bffgfedica   "
        "    bfffedda    "
        "    bdffddda    "
        "     aaaaaa     "
        "                "
	*/
	"\x11\x20\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x00\x80\x10\x82\x10\x02\x00\x00\x42\x70\xef\xbd\x07\x84\x00\xa1\xb5\xa5\x94\x52\x09\xc2\x20\x02\x5b\x4b\x29\x95\x52\x08\xc2\x84\xb0\x94\x52\x21\x8c\x20\x8c\x31\x21\x84\x90\xd2\x08\xc2\x98\x83\x4a\x29\x89\x8c\x00\x84\x39\xa6\x94\x92\x46\x00\x40\x18\x73\x4c\x21\x64\x04\x00\x84\x31\xc7\x14\x92\x46\x00\x00\x08\x63\x4c\x21\x24\x00\x00\x80\x20\xc6\x10\x42\x02\x00\x00\x80\x10\x42\x08\x01\x00\x00"
        ));

    add_image(12, 624, PSTR(
	/*
        "                "
        "                "
        "     aaabbb     "
        "   aarrssrqbb   "
        "  asrqrssrqqsa  "
        "  barssrssrqaa  "
        "  bfaasqrraaca  "
        "  bfffaaaassca  "
        "  bffgqeeerdca  "
        "   bfgfeeeqca   "
        "   bffgfeddca   "
        "   bffgfedqca   "
        "    bfffedda    "
        "    bdffddda    "
        "     aaaaaa     "
        "                "
	*/
	"\x0b\x20\x61\x62\x63\x64\x65\x66\x67\x71\x72\x73\x00\x10\x11\x22\x02\x00\x10\x91\xa9\x9a\x28\x02\xa1\x89\xa9\x9a\x88\x1a\x12\xa9\x9a\xaa\x89\x11\x62\x11\x8a\x99\x11\x13\x62\x66\x11\x11\xaa\x13\x62\x76\x58\x55\x49\x13\x20\x76\x56\x55\x38\x01\x20\x66\x67\x45\x34\x01\x20\x66\x67\x45\x38\x01\x00\x62\x66\x45\x14\x00\x00\x42\x66\x44\x14\x00\x00\x10\x11\x11\x01\x00"
	));

   
//    /* Gold block from http://i.imgur.com/ksa9hqZ.png */
//    imgs[4] = PSTR(
//        "abbbbaccdcabbbba"
//        "aaccccccbcccdaab"
//        "adbbbbbegbaadbaa"
//        "acaaddaefhbbbbba"
//        "accghbbbbbcccccd"
//        "bbaeeaabaddghbda"
//        "ccaaabbbaageeccd"
//        "aaabbbhgbdbbbbaa"
//        "ahddcefabdcccccc"
//        "afgbbbbaddbgebca"
//        "aegbcccbdbhfeaaa"
//        "deaabaaagcaccccd"
//        "abbbbbbggaaacbba"
//        "acbghaaeeabggacc"
//        "aaagebbbaaceebba"
//        "bbbbdccaaaabbbaa"
//        );
//
//    add_colourmap('a', 11, 127 >> 4, 127 >> 4, 127 >> 4);
//    add_colourmap('b', 12, 116 >> 4, 116 >> 4, 116 >> 4);
//    add_colourmap('c', 13, 143 >> 4, 143 >> 4, 143 >> 4);
//    add_colourmap('d', 14, 104 >> 4, 104 >> 4, 104 >> 4);
//    add_colourmap('e', 15, 248 >> 2, 175 >> 2,  42 >> 2);
//    add_colourmap('f', 16, 255 >> 2, 255 >> 2, 181 >> 2);
//    add_colourmap('g', 17, 252 >> 2, 238 >> 2,  75 >> 2);
//    add_colourmap('h', 18, 255 >> 2, 255 >> 2, 255 >> 2);
//    
//    /* Diamond block from http://i.imgur.com/ksa9hqZ.png */
//    imgs[5] = PSTR(
//        "abbbbaccdcabcbba"
//        "accccccdbccccbbb"
//        "aaaabbbikbaaabba"
//        "acaabbbjjlbbabca"
//        "acbdijbbbbabbccd"
//        "bcadkmbaabbimbba"
//        "caacbbababllmbcd"
//        "aabcaaijabbbbbaa"
//        "abkbckmabbcbbccc"
//        "ablibaabccdimaca"
//        "abmjbcbccbljmbaa"
//        "abkbcbbbibbbbccd"
//        "aabbbbbjicbcbaba"
//        "acbijbalkcbijbcc"
//        "aaakmbbdbbbkmbba"
//        "bbbbbccabbabbbaa"
//        );
//    add_colourmap('i', 19, 200 >> 2, 255 >> 2, 255 >> 2);
//    add_colourmap('j', 20, 141 >> 2, 255 >> 2, 255 >> 2);
//    add_colourmap('k', 21,   3 >> 2, 255 >> 2, 255 >> 2);
//    add_colourmap('l', 22,   3 >> 2, 223 >> 2, 228 >> 2);
//    add_colourmap('m', 23,   3 >> 2, 223 >> 2, 255 >> 2);

}

