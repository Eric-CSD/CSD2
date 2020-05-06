CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack

all: example

example : jack_module.o main.o sine.o generator.o oscillator.o synthesizer.o envelope.o clock.o subject.o
	$(CC) -o $@ $(CFLAGS) jack_module.o main.o sine.o generator.o oscillator.o synthesizer.o envelope.o clock.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
