all: main server client

main: main.o procedure.o
	gcc -o main main.o procedure.o -lpthread

client: client.o procedure.o
	gcc -o client client.o procedure.o

client.o: client.c header.h
	gcc -c client.c

server: server.o procedure.o
	gcc -o server server.o procedure.o -lpthread

server.o: server.c header.h
	gcc -c server.c

main.o: main.c header.h 
	gcc -c main.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f main
	rm -f server
	rm -f client
