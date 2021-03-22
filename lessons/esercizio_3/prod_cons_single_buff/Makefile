all: main

main: procedure.o semafori.o main.o
	gcc -o main procedure.o semafori.o main.o


main.o: main.c
	gcc -c main.c 


procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean: 
	rm -rf *.o
	rm -rf main
