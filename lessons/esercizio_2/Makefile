all: semafori

semafori: semafori.o procedure.o
	gcc -o semafori semafori.o procedure.o

semafori.o: semafori.c procedure.h
	gcc -c semafori.c -o semafori.o
procedure.o: procedure.c procedure.h
	gcc -c procedure.c -o procedure.o

clean:
	rm -rf *.o
	rm -rf semafori
