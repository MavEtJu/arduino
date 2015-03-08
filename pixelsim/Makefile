#

.SUFFIXES: .ino

# Remove the -O2 since it broke wrefresh(screen) from libcurses for some reason.
CFLAGS	= -Wall -Werror -I. -Wno-char-subscripts -g
CXXFLAGS	= ${CFLAGS}
.for o in ${OPTIONS}
CFLAGS+= -D${o}
.endfor

all:	.depend test StringEncodeMain

upload: all
	./test

.ino.o:
	${CXX} ${CXXFLAGS} -x c++ -o $@ -c $<

test: LED_Strip.o Arduino.o ArduinoMain.o Adafruit_NeoPixel.o ledsquare.o MemoryFree.o Serial.o StringEncode.o LED_Slideshow.o LED_Animation.o LED_Text.o A_Tools.o slides.o animations.o animation_squares.o
	${CXX} ${CXXFLAGS} -o $@ $> -lcurses

StringEncodeMain: StringEncode.o StringEncodeMain.o Arduino.o Serial.o A_Tools.o
	${CXX} ${CXXFLAGS} -o $@ $>

LINKFILES= \
	ledsquare.ino LED_Animation.cpp LED_Animation.h LED_Slideshow.cpp \
	LED_Slideshow.h LED_Text.cpp LED_Text.h A_Tools.cpp A_Tools.h \
	LED_Strip.ino LED_Strip.h StringEncode.h StringEncode.cpp \
	slides.h slides.cpp \
	animations.cpp animations.h animation_squares.cpp animation_squares.h
.for f in ${LINKFILES}
${f}:
	ln -fs ../ledsquare/${f} ${f}
.endfor
links: ${LINKFILES}

.depend: links
	make depends

clean:
	rm -f *.o *.core .depend test StringEncodeMain
	find . -type l -exec rm {} \;

depends:
	${CC} ${CXXFLAGS} -x c++ -M *.ino *.cpp > .depend
