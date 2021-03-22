#include "header.h"

void Inizializza(GestioneIO * g){
	pthread_mutex_init(&g->mutex, NULL);
	pthread_cond_init(&g->produttori, NULL);
	for(int i=0;i<10;i++){
		g->vettore[i].indirizzo=0;
		g->vettore[i].dato=0;
		g->stato[i]=VUOTO;
	}
	g->numero_occupati=0;
	g->numero_liberi=10;
}

void Produci(GestioneIO * g, Buffer * b){
	pthread_mutex_lock(&g->mutex);
	while(g->numero_liberi==0){
		pthread_cond_wait(&g->produttori, &g->mutex);
	}
	int i=0;
	while(i<10 && g->stato[i]!=VUOTO){i++;}
	g->stato[i]=INUSO;
	g->numero_liberi--;
	pthread_mutex_unlock(&g->mutex);
	g->vettore[i].indirizzo=b->indirizzo;
	g->vettore[i].dato=b->dato;
	printf("PRODUTTORE: ho fatto\n");
	pthread_mutex_lock(&g->mutex);
	g->stato[i]=PIENO;
	g->numero_occupati++;
	pthread_mutex_unlock(&g->mutex);
}

int Consuma(GestioneIO * g, Buffer * b){
	pthread_mutex_lock(&g->mutex);
	while(g->numero_occupati==0){
		pthread_mutex_unlock(&g->mutex);
		return 1;
	}
	int i=0;
	while(i<10 && g->stato[i]!=PIENO){i++;}
	g->stato[i]=INUSO;
	g->numero_occupati--;
	pthread_mutex_unlock(&g->mutex);
	b->indirizzo=g->vettore[i].indirizzo;
	b->dato=g->vettore[i].dato;
	pthread_mutex_lock(&g->mutex);
	g->stato[i]=VUOTO;
	g->numero_liberi++;
	pthread_cond_signal(&g->produttori);
	pthread_mutex_unlock(&g->mutex);
	return 0;
}

void *produttori(void * p){
	GestioneIO * g= (GestioneIO*) p;
	Buffer b;
	srand(time(NULL));
	b.indirizzo=rand()%11;
	b.dato=rand()%11;
	Produci(g,&b);
	sleep(1);
	b.indirizzo++;
	b.dato++;
	Produci(g,&b);
	sleep(1);
	b.indirizzo++;
	b.dato++;
	Produci(g,&b);
	sleep(1);
	pthread_exit(0);
}

void * consumatori(void * p){
	GestioneIO * g=(GestioneIO*) p;
	Buffer b;
	for(int i=0;i<4;i++){
		while(Consuma(g,&b)==0) printf("CONSUMATORE: valori consumati ---> DATO [%d] -----> INDIRIZZO [%d]\n", b.dato, b.indirizzo);
		sleep(3);
	}
	pthread_exit(0);
}
