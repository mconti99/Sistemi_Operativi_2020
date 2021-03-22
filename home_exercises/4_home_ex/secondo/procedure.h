#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include "monitor.h"

#define DIM 3

typedef struct{
	int buffer[DIM];
	int testa;
	int coda;
	Monitor m;
	int contatore;
}PriorityProdCons;


void inizializza_prod_cons(PriorityProdCons* p);
void produci_alta_prio(PriorityProdCons* p );
void produci_bassa_prio(PriorityProdCons* p);
void consuma(PriorityProdCons* p);
void rimuovi_prod_cons(PriorityProdCons* p);

#endif
