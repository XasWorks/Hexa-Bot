CC = avr-gcc
CFLAGS = -std=gnu++11

MCUSPEED = 16000000
CFLAGS += -DF_CPU=$(MCUSPEED)

TARGET = main.cpp

# generate the dependency list of the sources
%.deps : BUILD %.cpp
	$(CC) -MM $(@:.deps=.cpp) > BUILD/$@

%.o : %.cpp
	$(CC) $(CFLAGS) $(@:.o=.cpp)

# make the build dir
BUILD :
	mkdir BUILD

# clean up everything. Yay!
clean :
	rm -r -f BUILD
