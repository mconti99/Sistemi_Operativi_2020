#ifndef _PRODCONS_H_
#define _PRODCONS_H_

#include "monitor_hoare.h"

#define DIM 10

typedef struct {
    long vettore[DIM];
	Monitor m;
	int testa;
	int coda;
	int totale_elementi;
    
} ProdCons;

#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

void inizializza(ProdCons * p);
void consuma(ProdCons * p);
void produci(ProdCons * p, int val);
void rimuovi(ProdCons * p);

#endif
