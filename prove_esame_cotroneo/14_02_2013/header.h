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
#include "semafori.h"
#define MUTEXS 0
#define MUTEXN 1
#define MUTEXL 2
typedef struct{
	char appello[10];
	int numero_prenotati;
	int numero_lettori;
}struttura;
void docente(int ds_sem, struttura* s);
void studente(int ds_sem, struttura * s );

#endif
