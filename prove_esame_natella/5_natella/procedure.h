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
#include "monitor.h"
#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

typedef struct {
    unsigned int posizione;
    pid_t processo;
} richiesta;

typedef struct{
	richiesta r[10];
	int testa;
	int coda;
	int contatore;
	Monitor m;
}coda;

void produci(coda * c);
void consuma(coda * c, richiesta * r);

#endif
