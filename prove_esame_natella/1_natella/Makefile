all: start consumatori produttori

start: start.o procedure.o semafori.o
	gcc -o start start.o procedure.o semafori.o -lm

produttori: produttori.o procedure.o semafori.o
	gcc -o produttori produttori.o procedure.o semafori.o  -lm

produttori.o: produttori.c procedure.h semafori.h
	gcc -c produttori.c 

consumatori: consumatori.o procedure.o semafori.o
	gcc -o consumatori consumatori.o procedure.o semafori.o -lm

consumatori.o: consumatori.c procedure.h semafori.h
	gcc -c consumatori.c -lm

start.o: start.c procedure.h semafori.h
	gcc -c start.c -lm

procedure.o: procedure.c procedure.h semafori.h
	gcc -c procedure.c -lm 

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -f *.o
	rm -f *~
	rm -f start
	rm -f consumatori
	rm -f produttori


