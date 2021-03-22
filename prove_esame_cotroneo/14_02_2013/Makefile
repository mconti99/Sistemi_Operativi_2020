all: main studente docente

main: main.o procedure.o
	gcc -o main main.o procedure.o semafori.o

main.o: main.c header.h
	gcc -c main.c

studente: studente.o procedure.o
	gcc -o studente studente.o procedure.o semafori.o

studente.o: studente.c header.h 
	gcc -c studente.c

docente: docente.o procedure.o
	gcc -o docente docente.o procedure.o semafori.o

docente.o: docente.c header.h
	gcc -c docente.c

procedure.o: procedure.c header.h semafori.h
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o
	rm -f main
	rm -f studente
	rm -f docente
