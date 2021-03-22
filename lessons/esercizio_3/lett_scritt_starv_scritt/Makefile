all: main

main: main.o procedure.o semafori.o
	gcc -o main main.o semafori.o procedure.o
main.o: main.c procedure.h
	gcc -c main.c
procedure.o: procedure.c procedure.h
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o
	rm -f main
