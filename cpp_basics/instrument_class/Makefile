all: instrument_class

instrument_class : instrument_class.cpp	instrument_class.h
	g++ -c instrument_class.cpp

instrument.o	:	instrument.cpp	instrument_class.h
	g++ -c instrument.cpp

instrument_class	:	instrument_class.o instrument.o
	g++ -o instrument instrument_class.o instrument.o

clean:
	rm -f *.o instrument
