all: main

main: main.o monitor.o procedure.o
	gcc -o main main.o monitor.o procedure.o

main.o: main.c header.h monitor.h
	gcc -c main.c

monitor.o: monitor.c monitor.h
	gcc -c  monitor.c

procedure.o: procedure.c header.h monitor.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f main

