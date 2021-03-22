#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"

void produttore(int*p, int ds_sem){
	printf("produttore è fermo prima di wait\n");
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	//inizio sezione critica
	printf("produttore si sblocca dopo la wait\n");
	sleep(2);
	*p=rand() %100;
	//fine sezione critica
	printf("valore prod: %d\n", *p);
	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}
void consumatore(int *p, int ds_sem){
	printf("consumatore è fermo prima di wait\n");
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
	printf("consumatore si sblocca dopo la wait\n");
	sleep(2);//per simulare una consumazione
	printf("Il valore consumato è: %d\n", *p);
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
