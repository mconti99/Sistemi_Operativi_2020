all: start generatore elaboratore analizzatore

start: semafori.o start.o
	gcc -o start semafori.o start.o

start.o: start.c header.h semafori.h
	gcc -c start.c

generatore:  semafori.o generatore.o
	gcc -o generatore semafori.o generatore.o

generatore.o: generatore.c header.h semafori.h
	gcc -c generatore.c


elaboratore: semafori.o elaboratore.o
	gcc -o elaboratore semafori.o elaboratore.o

elaboratore.o: elaboratore.c header.h semafori.h
	gcc -c elaboratore.c


analizzatore:  semafori.o analizzatore.o
	gcc -o analizzatore semafori.o analizzatore.o

analizzatore.o: analizzatore.c header.h semafori.h
	gcc -c analizzatore.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf 
