#DEBUG = -DDEBUG_ 

all: meteo

meteo: meteo.o procedure.o monitor.o
	gcc -o meteo meteo.o procedure.o monitor.o

meteo.o: meteo.c header.h
	gcc -c -o meteo.o meteo.c

procedure.o: procedure.c header.h
	gcc -c -o procedure.o procedure.c

monitor.o: monitor.c monitor.h
	gcc -c -o monitor.o $(DEBUG) monitor.c

clean:
	rm -rf *.o
	rm -rf meteo
