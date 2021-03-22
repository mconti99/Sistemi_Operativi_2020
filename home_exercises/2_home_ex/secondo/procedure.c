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

void lettore1(buffer * p, int * num, int sem){
	InizioLettura(num, sem);
	sleep(2);
	printf("sto leggendo il val_1 del buffer %d \n", p->val_1);
	FineLettura(num,sem);
}
void lettore2(buffer * p, int * num, int sem){
        InizioLettura(num, sem);
        sleep(2);
        printf("sto leggendo il val_2 del buffer %d \n", p->val_2);
        FineLettura(num,sem);
}

void scrittore(buffer* p, int sem){
	InizioScrittura(sem);
	int i= rand()%10;
	int j=rand()%10;
	p->val_1=i;
	p->val_2=j;
	sleep(1);
	printf("sto scrivendo i valori %d e %d\n", i, j);
	FineScrittura(sem);
}
void InizioLettura(int * num, int sem){	
	Wait_Sem(sem, MUTEXL);
	(*num)=(*num)+1;
	if((*num)==1) Wait_Sem(sem, SYNCH);
	Signal_Sem(sem, MUTEXL);
}
void InizioScrittura(int sem){
	Wait_Sem(sem, SYNCH);
}
void FineScrittura( int sem){
	Signal_Sem(sem, SYNCH);
}
void FineLettura(int * num, int sem){
	Wait_Sem(sem, MUTEXL);
	(*num)--;
	if((*num)==0) Signal_Sem(sem, SYNCH);
	Signal_Sem(sem, MUTEXL);
}

