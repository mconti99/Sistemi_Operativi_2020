#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void StackInit(Stack * s, int dim) {

	/* TBD: Inizializzare mutex e variabili condition */
	pthread_mutex_init(&s->mutex, NULL);
	pthread_cond_init(&s->produttori, NULL);
	pthread_cond_init(&s->consumatori, NULL);


	s->dati = (Elem *) malloc(sizeof(Elem)*dim);
	s->dim = dim;
	s->testa = 0;
}


void StackRemove(Stack * s) {

	/* TBD: Disattivare mutex e variabili condition */
	pthread_mutex_destroy(&s->mutex);
	pthread_cond_destroy(&s->produttori);
	pthread_cond_destroy(&s->consumatori);
	free(s->dati);
}

void StackPush(Stack * s, Elem e) {

	/* TBD: Aggiungere la sincronizzazione */
	pthread_mutex_lock(&s->mutex);
	while(s->testa==s->dim){
		pthread_cond_wait(&s->produttori, &s->mutex);
	}

	
	s->dati[s->testa] = e;
	s->testa++;
	
	printf("Inserimento: %d\n", e);

	pthread_cond_signal(&s->consumatori);
	pthread_mutex_unlock(&s->mutex);

}


Elem StackPop(Stack * s) {

	int elemento;
	pthread_mutex_lock(&s->mutex);
	while(s->testa==0){
		pthread_cond_wait(&s->consumatori, &s->mutex);
	}

	/* TBD: Aggiungere la sincronizzazione */

	s->testa--;	
	elemento=s->dati[s->testa];

	printf("Prelievo: %d\n", elemento);
	
	pthread_cond_signal(&s->produttori);
	pthread_mutex_unlock(&s->mutex);
	return elemento;
}

int StackSize(Stack * s) {
	
	int size;

	/* TBD: Aggiungere la sincronizzazione */
	pthread_mutex_lock(&s->mutex);
	size = s->testa;
	printf("Numero attuale di elementi = %d\n", size);
	pthread_mutex_unlock(&s->mutex);

	return size;
}
