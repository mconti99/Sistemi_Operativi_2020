all: main

main: main.o procedure.o 
	gcc -o main main.o procedure.o

main.o: main.c header.h
	gcc -c main.c

procedure.o: header.h procedure.c
	gcc -c procedure.c




clean:
	rm -rf *.o
	rm -rf 
