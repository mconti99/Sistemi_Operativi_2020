#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define DIM 6

typedef int Frame[2][2];

typedef struct {

    Frame vettore[DIM];
    pthread_mutex_t mutex;
    pthread_cond_t produttori;
    pthread_cond_t consumatori;
    pthread_cond_t buffer;
    int testa;
    int coda;
    int contatore;
    /* TBD: Completare la struttura dati monitor */

} MonitorStreaming;

void inizializza(MonitorStreaming * m);
void produci(MonitorStreaming * m, Frame f);
void consuma(MonitorStreaming * m, Frame f);
void bufferizza(MonitorStreaming * m, int n);
void distruggi(MonitorStreaming * m);

#endif
