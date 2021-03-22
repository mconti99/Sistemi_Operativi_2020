#ifndef _HEADER_H
#define _HEADER_H

#include "monitor.h"
#define DIM 5

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

struct ProdCons{
	int buffer[DIM];
	int stato[DIM];

	int numero_occupati;
	int numero_liberi;
	Monitor m;
};
#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

void Produci(struct ProdCons *pc, int valore);
int Consuma(struct ProdCons *pc);
#endif
