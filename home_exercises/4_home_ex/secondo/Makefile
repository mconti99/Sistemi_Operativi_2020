all: main.o procedure.o monitor.o
	gcc -o start main.o procedure.o monitor.o

main.o: main.c procedure.o monitor.o
	gcc -c main.c

procedure.o: procedure.c procedure.h monitor.o
	gcc -c procedure.c

monitor.o: monitor.c monitor.h
	gcc -c monitor.c
      
clean:
	rm -f *.o 
	rm -f start
