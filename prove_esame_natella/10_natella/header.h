#ifndef _HEADER_H
#define _HEADER_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/msg.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

#define DIM 5
#define TYPE1 1

#define RTS 2
#define OTS 3
extern int coda_richieste1, coda_richieste2, coda_risposte;
extern int coda_RTS, coda_OTS;

typedef struct{
	long pid;
	int valore;
}msg;

typedef struct{
	msg vettore[DIM];
	int testa;
	int coda; 
	int contatore;

	pthread_cond_t consumatori;
	pthread_mutex_t mutex;
}monitor;

void client();
void * consumatore(void *);
void * produttore(void *);
void server();
void init();
void removeCodeServizio();
#endif
