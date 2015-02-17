#

.SUFFIXES: .ino

# Remove the -O2 since it broke wrefresh(screen) from libcurses for some reason.
CFLAGS	= -Wall -Werror -I. -Wno-char-subscripts -g

all:	test StringEncodeMain

.ino.o:
	${CXX} ${CXXFLAGS} -x c++ -o ${.TARGET} -c ${.IMPSRC}

test: led_tools.o Arduino.o ArduinoMain.o Adafruit_NeoPixel.o toiletroll_draw.o MemoryFree.o Serial.o StringEncode.o
	${CXX} ${CXXFLAGS} -o ${.TARGET} ${.ALLSRC} -lcurses

StringEncodeMain: StringEncode.o StringEncodeMain.o Arduino.o Serial.o
	${CXX} ${CXXFLAGS} -o ${.TARGET} ${.ALLSRC}

test.o: test.ino
led_tools.o: led_tools.ino led_tools.h Arduino.h Adafruit_NeoPixel.h
toiletroll_draw.o: toiletroll_draw.ino led_tools.h MemoryFree.h Arduino.h
Arduino.o: Arduino.cpp Arduino.h Serial.h
ArduinoMain.o: ArduinoMain.cpp Arduino.h Serial.h
MemoryFree.o: MemoryFree.cpp MemoryFree.h
Serial.o: Serial.cpp Serial.h
StringEncode.o: StringEncode.cpp StringEncode.h Arduino.h
StringEncodeMain.o: StringEncodeMain.cpp StringEncode.h Arduino.h
Adafruit_NeoPixel.o: Adafruit_NeoPixel.cpp Adafruit_NeoPixel.h Arduino.h Serial.h
Arduino.cpp: Arduino.h
Arduino.h: Serial.h

toiletroll_draw.ino: led_tools.h Arduino.h
	ln -fs ../toiletroll_draw/toiletroll_draw.ino toiletroll_draw.ino
led_tools.ino:
	ln -fs ../toiletroll_draw/led_tools.ino led_tools.ino
led_tools.h:
	ln -fs ../toiletroll_draw/led_tools.h led_tools.h

clean:
	rm -f *.o test led_tools.ino led_tools.h toiletroll_draw.ino StringEncodeMain *.core
