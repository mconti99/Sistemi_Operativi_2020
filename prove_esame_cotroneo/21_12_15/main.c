#include "header.h"

int main(){
	GestioneIO* g=malloc(sizeof(GestioneIO));
	pthread_attr_t attr;
	pthread_t prod[4];
	pthread_t cons[2];

	pthread_attr_init(&attr);
	Inizializza(g);

	for(int i=0;i<4;i++) pthread_create(&prod[i], &attr, produttori, (void*) g);
	for(int i=0;i<2;i++) pthread_create(&cons[i], &attr, consumatori, (void*) g);
	
	for(int i=0;i<4;i++) pthread_join(prod[i], NULL);
	for(int i=0;i<2;i++) pthread_join(cons[i], NULL);
	pthread_attr_destroy(&attr);
	free(g);
	pthread_exit(0);
}
