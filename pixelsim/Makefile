#

.SUFFIXES: .ino

CFLAGS	+= -Wall -Werror -I. -Wno-char-subscripts -g

all:	led_tools

.ino.o:
	${CXX} ${CXXFLAGS} -x c++ -o ${.TARGET} -c ${.ALLSRC}

led_tools: led_tools.o Arduino.o Adafruit_NeoPixel.o test.o
	${CXX} ${CXXFLAGS} -o ${.TARGET} ${.ALLSRC}


test.o: test.ino
led_tools.o: led_tools.ino
Arduino.o: Arduino.cpp Arduino.h
Adafruit_NeoPixel.o: Adafruit_NeoPixel.cpp Adafruit_NeoPixel.h Arduino.h
Arduino.cpp: Arduino.h

test.ino: led_tools.h Arduino.h
	ln -fs ../toiletroll_draw/toiletroll_draw.ino test.ino
led_tools.ino: led_tools.h Adafruit_NeoPixel.h Arduino.h
	ln -fs ../toiletroll_draw/led_tools.ino led_tools.ino
led_tools.h:
	ln -fs ../toiletroll_draw/led_tools.h led_tools.h

clean:
	rm -f *.o led_tools led_tools.ino led_tools.h test.ino
