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
#include "semafori.h"

#define MESSAGGIO_DISPONIBILE0 0
#define MESSAGGIO_DISPONIBILE1 1
#define MESSAGGIO_DISPONIBILE2 2
#define SPAZIO_DISPONIBILE 3
#define MUTEXP 4

#define OCCUPATO 0
#define INUSO 1
#define LIBERO 2

typedef struct{
	int chiave;
	int valore;
}buffer;

typedef struct{
	buffer vettore[4];
	int stato[4];
}struttura;

void produci(int ds_sem, struttura * s, buffer b);
void consuma(int ds_sem, struttura * s, int i, buffer * b);
#endif
