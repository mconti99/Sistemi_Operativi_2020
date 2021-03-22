#include <pthread.h>
#ifndef HEADER_H
#define HEADER_H

typedef long msg;
struct LettScritt{
	pthread_mutex_t mutex;
	pthread_cond_t lettori;
	pthread_cond_t scrittori;

	int num_lettori;
	int num_scrittori;
	int num_lettori_wait;
	int num_scrittori_wait;
	msg mess;
};

void * lettore(void*);
void * scrittore(void*);

void scrivi(struct LettScritt* ls, msg m);
msg leggi(struct LettScritt * ls);

void InizioLettura(struct LettScritt * ls);
void InizioScrittura(struct LettScritt * ls);
void FineLettura(struct LettScritt * ls);
void FineScrittura(struct LettScritt * ls);
#endif
