all: main analizzatore elaboratore generatore

main: procedure.o semafori.o main.o
	gcc -o main  procedure.o semafori.o main.o

main.o: main.c semafori.h procedure.h 
	gcc -c main.c
analizzatore: procedure.o semafori.o analizzatore.o
	gcc -o analizzatore procedure.o semafori.o analizzatore.o

elaboratore: procedure.o semafori.o elaboratore.o
	gcc -o elaboratore procedure.o semafori.o elaboratore.o

elaboratore.o: elaboratore.c semafori.h procedure.h
	gcc -c elaboratore.c
generatore: procedure.o semafori.o generatore.o
	gcc -o generatore procedure.o semafori.o generatore.o

generatore.o: generatore.c semafori.h procedure.h
	gcc -c generatore.c


analizzatore.o: analizzatore.c semafori.h procedure.h
	gcc -c analizzatore.c


procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf prodcons_coda_circolare
