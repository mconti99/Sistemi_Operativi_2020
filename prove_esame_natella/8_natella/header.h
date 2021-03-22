#ifndef _HEADER_H
#define _HEADER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

typedef struct { 
	int a;
       	int b; 
} elemento;

typedef struct {
    elemento vettore[5];
	int testa;
	int coda;
	int contatore;
	pthread_mutex_t mutex;
	pthread_cond_t produttore;
	pthread_cond_t consumatore;
} MonitorVettore;

typedef struct {
    elemento buffer;
    int num_lettori;
    int num_scrittori;
    pthread_mutex_t mutex;
    pthread_cond_t scrittore;
    pthread_cond_t lettore;
} MonitorBuffer;

typedef struct{
	MonitorVettore* v;
	MonitorBuffer* b;
}agg;

void genera(MonitorVettore *v, elemento e);
elemento preleva(MonitorVettore *v);
void aggiorna(MonitorBuffer *b, elemento e);
void consulta(MonitorBuffer *b);

void * generatore(void *);
void * aggiornatore(void *);
void * destinatario(void *);
#endif
