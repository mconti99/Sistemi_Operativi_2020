all: main

main:main.o procedure.o monitor.o
	gcc -o main main.o procedure.o monitor.o
main.o: main.c
	gcc -c main.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

monitor.o: monitor.c monitor.h
	gcc -c monitor.c



clean:
	rm -rf *.o
	rm -rf main
