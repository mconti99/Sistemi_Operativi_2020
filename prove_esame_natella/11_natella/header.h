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

extern coda_richieste, coda_risposte;
typedef struct{
	long pid;
	int valore1;
	int valore2;
}msg;

typedef struct{
	long pid;
	int prod;
}msg1;

typedef struct{
	msg buffer[2];
	int contatore;
	int testa;
	int coda;
	pthread_mutex_t mutex;
	pthread_cond_t produttori;
	pthread_cond_t consumatori;
}struttura;

void client();

#endif
