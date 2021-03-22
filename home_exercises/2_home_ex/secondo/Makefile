all: start lettore scrittore lettore1

start: start.o semafori.o  procedure.o 
	gcc -o start start.o procedure.o semafori.o

scrittore: scrittore.o semafori.o procedure.o
	gcc -o scrittore scrittore.o procedure.o semafori.o
lettore1: lettore1.o semafori.o procedure.o
	gcc -o lettore1 lettore1.o procedure.o semafori.o
lettore: lettore.o semafori.o procedure.o
	gcc -o lettore lettore.o  procedure.o semafori.o
start.o: start.c procedure.h semafori.h
	gcc -c start.c
scrittore.o: scrittore.c procedure.h semafori.h
	gcc -c scrittore.c
lettore1.o: lettore1.c procedure.h semafori.h
	gcc -c lettore1.c
lettore.o: lettore.c procedure.h semafori.h
	gcc -c lettore.c
procedure.o: procedure.c procedure.h semafori.h
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o
	rm -f scrittore lettore start
