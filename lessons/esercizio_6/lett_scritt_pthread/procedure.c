#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "header.h"

void * scrittore(void *p){
	struct LettScritt * ls=(struct LettScritt *)p;
	int i;
	for(i=0;i<3;i++){
		struct timeval t1;
		struct timezone t2;

		gettimeofday(&t1, &t2);
		msg m=t1.tv_usec;
		scrivi(ls, m);
	}
	pthread_exit(0);
}

void* lettore(void * p){
	struct LettScritt * ls=(struct LettScritt*)p;
	int i;
	for(i=0;i<3;i++){
		msg m=leggi(ls);
	}

	pthread_exit(0);
}

msg leggi(struct LettScritt * ls){
	msg m;
	InizioLettura(ls);
	int tid=syscall(SYS_gettid);
	printf("Thread #%d, valore letto = [%ld]\n", tid, ls->mess);
	m=ls->mess;
	FineLettura(ls);
	return m;
}

void scrivi(struct LettScritt * ls, msg m){
	InizioScrittura(ls);
	int tid=syscall(SYS_gettid);
	ls->mess=m;
	printf("Thread #%d, valore scritto [%ld]\n", tid, ls->mess);
	FineScrittura(ls);
}

void InizioLettura(struct LettScritt * ls){
	pthread_mutex_lock(&ls->mutex);

	while(ls->num_scrittori>0){
		ls->num_lettori_wait++;
		pthread_cond_wait(&ls->lettori, &ls->mutex);
		ls->num_lettori_wait--;
	}

	ls->num_lettori++;

	pthread_mutex_unlock(&ls->mutex);
}

void FineLettura(struct LettScritt * ls){
	pthread_mutex_lock(&ls->mutex);
	ls->num_lettori--;
	if(ls->num_lettori==0) pthread_cond_signal(&ls->scrittori);

	pthread_mutex_unlock(&ls->mutex);
}

void InizioScrittura(struct LettScritt * ls){
	pthread_mutex_lock(&ls->mutex);
	while(ls->num_lettori> 0 || ls->num_scrittori>0){
		ls->num_scrittori_wait++;
		pthread_cond_wait(&ls->scrittori, &ls->mutex);
		ls->num_scrittori_wait--;
	}

	ls->num_scrittori++;
	pthread_mutex_unlock(&ls->mutex);
}

void FineScrittura(struct LettScritt * ls){
	pthread_mutex_lock(&ls->mutex);
	ls->num_scrittori--;
	if(ls->num_scrittori_wait>0){
		pthread_cond_signal(&ls->scrittori);
	}else{
		pthread_cond_broadcast(&ls->lettori);
	}
	pthread_mutex_unlock(&ls->mutex);
}
