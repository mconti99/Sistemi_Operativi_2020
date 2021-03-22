#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "header.h"

int coda_risultati;

#define NUM_THREADS_OPERANDI    2
#define NUM_THREADS_CALCOLO     3

int main(){

        pthread_attr_t attr;
        pthread_t threads_operandi[NUM_THREADS_OPERANDI];
        pthread_t threads_calcolo[NUM_THREADS_CALCOLO];

        srand(time(NULL)*getpid());

        // Creazione coda risultati
        coda_risultati = msgget(IPC_PRIVATE, IPC_CREAT|0664);
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
            
        //creazione di una istanza di struttura monitor per gli operandi
        // MonitorOperandi sarà usato dai thread generazione operandi
        MonitorOperandi * pc_op = malloc(sizeof(MonitorOperandi));
    
        //inizializzazione mutex e condition
        pthread_mutex_init(&pc_op->mutex, NULL);
	pthread_cond_init(&pc_op->consumatori, NULL);
	pthread_cond_init(&pc_op->produttori, NULL);
    
        //inizializzazione delle variabili di stato
    	pc_op->testa=0;
    	pc_op->coda=0;
    	pc_op->contatore=0;

    
        //impostazione dei thread come joinable
	pthread_attr_init(&attr);
    
        // genero processo prelievo risultati
    
        pid_t pid;
	pid=fork();
        if(pid==0){
		preleva_risultati(coda_risultati);
	}
        // genero thread generazione operandi
        for(int i=0;i<NUM_THREADS_OPERANDI;i++){
		pthread_create(&threads_operandi[i], &attr, genera_operandi, (void*) pc_op);
	}
    
        // genero thread di calcolo
        for(int i=0;i<NUM_THREADS_CALCOLO;i++){
		pthread_create(&threads_calcolo[i], &attr, calcola, (void*) pc_op);
	}
    
        /* TBD:  Join threads a wait processo*/
	for(int i=0;i<NUM_THREADS_CALCOLO;i++){
		pthread_join(threads_calcolo[i], NULL);
	}

	for(int i=0;i<NUM_THREADS_OPERANDI;i++){
		pthread_join(threads_operandi[i], NULL);
	}
   	wait(NULL);
    
        /*deallocazione risorse*/

        pthread_attr_destroy(&attr);
	pthread_cond_destroy(&pc_op->produttori),
	pthread_cond_destroy(&pc_op->consumatori);
	pthread_mutex_destroy(&pc_op->mutex);
    	free(pc_op);
	removeServiceQueues();
        pthread_exit(NULL);
}

