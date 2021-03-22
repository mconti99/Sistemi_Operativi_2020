#include "monitor.h"

#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

struct ProdCons{
	Monitor m;
	int buffer; //risorsa che deve essere acceduta nella sezione critica
	int buffer_libero;
	int buffer_occupato;
};

void Produci(struct ProdCons *, int valore);
void Consuma(struct ProdCons *);
