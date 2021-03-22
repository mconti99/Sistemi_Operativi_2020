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
#include "monitor.h"
#include <math.h>
#define N 20
#define PRODUTTORI 1
#define CONSUMATORI 0
typedef struct{
	int buffer[N];
	int testa;
	int coda;
	int contatore;
	Monitor m;
}prodcons;

void produci(prodcons* p, int valore);
void consuma(prodcons* p);
#endif
