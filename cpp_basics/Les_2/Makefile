all: osc_test

oscillator.o : oscillator.cpp	oscillator.h
	g++ -c oscillator.cpp

oscillator_test.o	:	oscillator_test.cpp	oscillator.h
	g++ -c oscillator_test.cpp

osc_test	:	oscillator.o oscillator_test.o
	g++ -o osc_test oscillator.o oscillator_test.o

clean:
	rm -f *.o osc_test
