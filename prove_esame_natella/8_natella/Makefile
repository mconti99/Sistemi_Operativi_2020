eseguibile: main.o procedure.o
	gcc main.o procedure.o  -o eseguibile -lpthread

main.o: main.c header.h
	gcc -c main.c -o main.o

procedure.o: procedure.c header.h
	gcc -c procedure.c -o procedure.o

clean:
	rm -f *.o
	rm -f eseguibile
