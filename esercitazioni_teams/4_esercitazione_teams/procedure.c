#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;
	
	m->num_scrittori=0;
	m->num_scrittori_wait=0;
	m->num_lettori=0;

	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->scrittori, NULL);
	pthread_cond_init(&m->lettori, NULL);

}

void rimuovi (struct monitor* m){
	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->scrittori);
	pthread_cond_destroy(&m->lettori);
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){
	pthread_mutex_lock(&m->mutex);
	while(m->num_lettori>0 || m->num_scrittori>0){
		m->num_scrittori_wait++;
		pthread_cond_wait(&m->scrittori, &m->mutex);
		m->num_scrittori_wait--;
	}
	m->num_scrittori++;
	pthread_mutex_unlock(&m->mutex);

	m->molo=molo;

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
int leggi_molo(struct monitor* m){
	int molo;
	pthread_mutex_lock(&m->mutex);
	while(m->num_scrittori>0){
		pthread_cond_wait(&m->lettori, &m->mutex);
	}
	m->num_lettori++;
	pthread_mutex_unlock(&m->mutex);
	
	molo=m->molo;

	pthread_mutex_lock(&m->mutex);
	m->num_lettori--;
	if(m->num_lettori==0) pthread_cond_signal(&m->scrittori);
	pthread_mutex_unlock(&m->mutex);
	return molo;

}

