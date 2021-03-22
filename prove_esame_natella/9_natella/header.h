#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


struct monitor {

	int stazione;
	int id_treno;
	int num_scrittori;
	int num_lettori;
	int num_scrittori_wait;
	pthread_mutex_t mutex;
	pthread_cond_t lettori;
	pthread_cond_t scrittori;
	
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_stazione(struct monitor * m, int stazione);
int leggi_stazione(struct monitor * m);



#endif
