#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "header.h"

#define NUM_THREADS 5
int main(){
	pthread_attr_t attr;
	pthread_t threads[NUM_THREADS];

	struct LettScritt * ls=malloc(sizeof(struct LettScritt));
	pthread_mutex_init(&ls->mutex, NULL);
	pthread_cond_init(&ls->lettori, NULL);
	pthread_cond_init(&ls->scrittori, NULL);

	ls->num_lettori=0;
	ls->num_scrittori=0;
	ls->num_lettori_wait=0;
	ls->num_scrittori_wait=0;

	pthread_attr_init(&attr);
	
	int k;
	for(k=0;k<NUM_THREADS;k++){
		if(k%2){
			printf("sono il thread lettore %d\n", k);
			pthread_create(&threads[k], &attr, lettore, (void*)ls);
		}else{
			sleep(1);
			printf("sono il thread scrittore %d\n", k);
			pthread_create(&threads[k], &attr, scrittore, (void*)ls);
		}
	}

	for(k=0;k<NUM_THREADS;k++){
		pthread_join(threads[k], NULL);
	}

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&ls->mutex);
	pthread_cond_destroy(&ls->lettori);
	pthread_cond_destroy(&ls->scrittori);
	free(ls);

	pthread_exit(NULL);
}
