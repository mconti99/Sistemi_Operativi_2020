#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM_BUFFER 5

/* TBD: Definire le macro per la comunicazione su coda sincrona */
#define TYPE1 1
#define TYPE2 2
#define TYPEMESS 3

extern int coda_RTS;
extern int coda_OTS;
extern int coda_risultati;

typedef struct {
    
    // pool di buffer condivisi
    int operandi[DIM_BUFFER];
    int testa;
    int coda;
    int contatore;
    pthread_mutex_t mutex;
    pthread_cond_t produttori;
    pthread_cond_t consumatori;
    
} MonitorOperandi;

typedef struct {
    /* TBD: Definire la struttura messaggio */
	long type;
	int valore;
} Risultato;

void inserisci_operando(MonitorOperandi * mo, int operando);
int *preleva_operando(MonitorOperandi * mo);

void inserisci_risultato(Risultato *m , int queue);
int preleva_risultato(Risultato *m, int queue, int tipomess);

void * genera_operandi(void *);
void * calcola(void *);
void preleva_risultati(int);

void initServiceQueues();
void removeServiceQueues();
    
#endif

