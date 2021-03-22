#ifndef _HEADER_H
#define _HEADER_H
#include <pthread.h>

/* ERRORE
#define OK_PROD 0
#define OK_CONS 1
*/
typedef long msg;
struct ProdCons{
	msg mess;
	int ok_produzione;
	int ok_consumo;
	//non devo dichiarare un monitor
	//faccio un mutex (accesso al monitor)
	//e 2 variabili condition: (posso produrre), (posso consumare)
	
	pthread_mutex_t mutex;
	pthread_cond_t ok_prod_cv;
	pthread_cond_t ok_cons_cv;
};

void * consumatore(void *);
void * produttore(void*);

void Produci(struct ProdCons*, msg m);
void Consuma(struct ProdCons*, msg m);

#endif
