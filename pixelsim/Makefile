#

.SUFFIXES: .ino

# Remove the -O2 since it broke wrefresh(screen) from libcurses for some reason.
CFLAGS	= -Wall -Werror -I. -Wno-char-subscripts -g
CXXFLAGS	= ${CFLAGS}

all:	test StringEncodeMain

.ino.o:
	${CXX} ${CXXFLAGS} -x c++ -o $@ -c $<

test: LED_Strip.o Arduino.o ArduinoMain.o Adafruit_NeoPixel.o ledsquare.o MemoryFree.o Serial.o StringEncode.o LED_Slideshow.o LED_Animation.o LED_Text.o A_Tools.o slides.o animations.o
	${CXX} ${CXXFLAGS} -o $@ $> -lcurses

StringEncodeMain: StringEncode.o StringEncodeMain.o Arduino.o Serial.o A_Tools.o
	${CXX} ${CXXFLAGS} -o $@ $>

test.o: test.ino
LED_Strip.o: LED_Strip.ino LED_Strip.h Arduino.h Adafruit_NeoPixel.h
ledsquare.o: ledsquare.ino LED_Strip.h MemoryFree.h Arduino.h \
	StringEncode.h LED_Animation.h LED_Slideshow.h LED_Text.h
LED_Slideshow.o: LED_Slideshow.cpp LED_Slideshow.h Arduino.h LED_Strip.h
LED_Animation.o: LED_Animation.cpp LED_Animation.h Arduino.h
LED_Text.o: LED_Text.cpp LED_Text.h LED_Strip.h Arduino.h
Arduino.o: Arduino.cpp Arduino.h Serial.h
ArduinoMain.o: ArduinoMain.cpp Arduino.h Serial.h
MemoryFree.o: MemoryFree.cpp MemoryFree.h
Serial.o: Serial.cpp Serial.h
A_Tools.o: A_Tools.cpp A_Tools.h
StringEncode.o: StringEncode.cpp StringEncode.h Arduino.h
StringEncodeMain.o: StringEncodeMain.cpp StringEncode.h Arduino.h
Adafruit_NeoPixel.o: Adafruit_NeoPixel.cpp Adafruit_NeoPixel.h Arduino.h \
	Serial.h
Arduino.cpp: Arduino.h
Arduino.h: Serial.h A_Tools.h
ledsquare.ino: LED_Strip.h Arduino.h slides.h animations.h
slides.cpp: slides.h
animations.cpp: animations.h

LINKFILES= \
	ledsquare.ino LED_Animation.cpp LED_Animation.h LED_Slideshow.cpp \
	LED_Slideshow.h LED_Text.cpp LED_Text.h A_Tools.cpp A_Tools.h \
	LED_Strip.ino LED_Strip.h StringEncode.h StringEncode.cpp \
	slides.h slides.cpp animations.cpp animations.h
.for f in ${LINKFILES}
${f}:
	ln -fs ../ledsquare/${f} ${f}
.endfor


clean:
	rm -f *.o test *.core
	find . -type l -exec rm {} \;
