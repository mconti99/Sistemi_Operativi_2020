all: main visualizzatore

main: procedure.o semafori.o main.o
	gcc -o main procedure.o semafori.o main.o

visualizzatore: visualizzatore.o semafori.o procedure.o
	gcc -o visualizzatore procedure.o semafori.o visualizzatore.o

visualizzatore.o: visualizzatore.c
	gcc -c visualizzatore.c
main.o: main.c procedure.h semafori.h
	gcc -c main.c

procedure.o: procedure.h procedure.c semafori.h
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf main
	rm -rf visualizzatore
