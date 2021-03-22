#ifndef _HEADER_H
#define _HEADER_H
#include <sys/types.h>
#include <sys/ipc.h>
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
extern int queue_risposta, queue_richiesta;
typedef struct{
	long type;
	int numero1;
	int numero2;
}msg;

typedef struct{
	long type;
	int prod;
}msg1;
typedef struct{
	msg m;
	pthread_mutex_t mutex;
}struttura;

void client();
void server();
void * produttore(void *);
#endif
