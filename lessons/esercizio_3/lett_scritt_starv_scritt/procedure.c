#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "procedure.h"
#include "semafori.h"

void InizioLettura(int sem, Buffer* buf){
	Wait_Sem(sem, MUTEXL); //indica ai lettori che sto iniziando a leggere, incremento numlettori in mutua esclusione
	buf->numlettori=buf->numlettori +1;
	if(buf->numlettori==1) Wait_Sem(sem, SYNCH); //non posso far scrivere agli scrittori mentre leggo
	Signal_Sem(sem, MUTEXL);
}
void FineLettura(int sem, Buffer* buf){
	Wait_Sem(sem, MUTEXL);//indica ai lettori che sto terminando la lettura, decrementando numlettori in mutua esclusione
	buf->numlettori=buf->numlettori-1;
	if(buf->numlettori==0) Signal_Sem(sem, SYNCH);// se sono l'ultimo lettore devo rilasciare la risorsa per gli scrittori
	Signal_Sem(sem, MUTEXL); //rilascio il mutex per altri lettori
}

void lettore(int sem, Buffer * buf){
	InizioLettura(sem, buf);
	sleep(1); //per simulare un ritardo di lettura
	printf("leggo %ld, numero lettori=%d\n", buf->messaggio, buf->numlettori);
	FineLettura(sem, buf);
}
void InizioScrittura(int sem){
	Wait_Sem(sem, SYNCH);
}
void FineScrittura(int sem){
	Signal_Sem(sem, SYNCH);
}
void scrittore(int sem, Buffer* buf){
	InizioScrittura(sem);
	struct timeval t1;
	struct timezone t2;
	gettimeofday(&t1,&t2); //per avere un valore diverso ad ogni produzione
	msg val=t1.tv_usec; 
	buf->messaggio=val;
	sleep(1);
	printf("Valore scritto=<%ld> \n", buf->messaggio);
	FineScrittura(sem);
}
