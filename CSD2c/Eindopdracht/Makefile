CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack -Wall

all: example

example : jack_module.o main.o stutterEffect.o circBuffer.o osc.o oscillator.o sine.o lfo_sine.o distortion.o
	$(CC) -o $@ $(CFLAGS) jack_module.o main.o stutterEffect.o circBuffer.o osc.o oscillator.o sine.o lfo_sine.o distortion.o -llo $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
