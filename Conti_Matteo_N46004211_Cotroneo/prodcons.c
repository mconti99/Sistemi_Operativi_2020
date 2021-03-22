#include "prodcons.h"

#include <stdio.h>


void inizializza(MonitorStreaming * m) {

    /* TBD: Inizializzare il monitor */
	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->produttori, NULL);
	pthread_cond_init(&m->consumatori, NULL);
	pthread_cond_init(&m->buffer, NULL);
	m->testa=0;
	m->coda=0;
	m->contatore=0;
}

void produci(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
	pthread_mutex_lock(&m->mutex);
	while(m->contatore==DIM){
		pthread_cond_wait(&m->produttori, &m->mutex);
	}


    printf("Produzione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

    m->vettore[m->testa][0][0] = f[0][0];
    m->vettore[m->testa][0][1]= f[0][1];
    m->vettore[m->testa][1][0] = f[1][0];
    m->vettore[m->testa][1][1] = f[1][1];
    m->testa=(m->testa+1)%DIM;
    m->contatore++;
    pthread_cond_signal(&m->buffer);
    pthread_mutex_unlock(&m->mutex);

}

void consuma(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
	pthread_mutex_lock(&m->mutex);
	while(m->contatore==0){
		pthread_cond_wait(&m->consumatori, &m->mutex);
	}

    f[0][0] = m->vettore[m->coda][0][0];
    f[0][1] = m->vettore[m->coda][0][1];
    f[1][0] = m->vettore[m->coda][1][0];
    f[1][1] = m->vettore[m->coda][1][1];

    printf("Consumazione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);
	m->coda=(m->coda+1)%DIM;
	m->contatore--;
	pthread_cond_signal(&m->produttori);
	pthread_mutex_unlock(&m->mutex);
}

void bufferizza(MonitorStreaming * m, int n) {

    pthread_mutex_lock(&m->mutex);
    while(m->contatore<n){
	    pthread_cond_wait(&m->buffer, &m->mutex);
    }
    pthread_cond_signal(&m->consumatori);

	pthread_mutex_unlock(&m->mutex);

}

void distruggi(MonitorStreaming * m) {

    pthread_mutex_destroy(&m->mutex);
        pthread_cond_destroy(&m->produttori);
        pthread_cond_destroy(&m->consumatori);
	pthread_cond_destroy(&m->buffer);
}
