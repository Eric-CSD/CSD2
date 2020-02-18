CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack -lncurses

all: SynthSong

SynthSong : jack_module.o oscillator.o square.o sine.o saw.o synthesizer.o main.o melodygenerator.o
	$(CC) -o $@ $(CFLAGS) jack_module.o oscillator.o sine.o square.o saw.o synthesizer.o main.o melodygenerator.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
