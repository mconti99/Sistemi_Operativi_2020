eeguibile: main.o procedure.o monitor.o
	gcc -o eseguibile  main.o procedure.o monitor.o

main.o: main.c procedure.h
	gcc -o main.o -c   main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c   procedure.c

monitor.o: monitor.c monitor.h
	gcc -o monitor.o -c   monitor.c

clean:
	rm -f eseguibile
	rm -f *.o
