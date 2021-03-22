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

#define PIENO 1
#define VUOTO 2
#define INUSO 3

typedef struct {
int indirizzo;
int dato;
} Buffer;

typedef struct {
Buffer vettore[10];
int stato[10];
int numero_occupati;
int numero_liberi;
pthread_mutex_t mutex;
pthread_cond_t produttori;
} GestioneIO;

void Inizializza(GestioneIO * g);
void Produci(GestioneIO * g, Buffer * b);
int Consuma(GestioneIO * g, Buffer * b);
void * produttori(void * p);
void * consumatori(void * p);

#endif
