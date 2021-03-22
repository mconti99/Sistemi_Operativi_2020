#include "header.h"


void inizializza(struct monitor* m){

	m->stazione=0;
	m->id_treno=0;
	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->lettori, NULL);
	pthread_cond_init(&m->scrittori, NULL);
	m->num_scrittori=0;
	m->num_lettori=0;
	m->num_scrittori_wait=0;
}

void rimuovi (struct monitor* m){

	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->lettori);
	pthread_cond_destroy(&m->scrittori);
}


void scrivi_stazione(struct monitor* m, int stazione){
	pthread_mutex_lock(&m->mutex);
	while(m->num_lettori>0 || m->num_scrittori>0){
		m->num_scrittori_wait++;
		pthread_cond_wait(&m->scrittori, &m->mutex);
		m->num_scrittori_wait--;
	}
	m->num_scrittori++;
	pthread_mutex_unlock(&m->mutex);

	// SCRITTURA
	m->stazione=stazione;

	pthread_mutex_lock(&m->mutex);
	m->num_scrittori--;
	if(m->num_scrittori_wait>0){
		pthread_cond_signal(&m->scrittori);
	}else{
		pthread_cond_broadcast(&m->lettori);
	}
	pthread_mutex_unlock(&m->mutex);

}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_stazione(struct monitor* m){
	pthread_mutex_lock(&m->mutex);
	while(m->num_scrittori>0){
		pthread_cond_wait(&m->lettori, &m->mutex);
	}
	m->num_lettori++;
	pthread_mutex_unlock(&m->mutex);

	// LETTURA
	int ris=m->stazione;
	
	pthread_mutex_lock(&m->mutex);
	m->num_lettori--;
	if(m->num_lettori==0) pthread_cond_signal(&m->scrittori);
	pthread_mutex_unlock(&m->mutex);
	return ris;
}
