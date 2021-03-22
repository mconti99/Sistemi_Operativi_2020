#include "header.h"

int main(){
	pthread_attr_t attr;
	pthread_t threads[5];

	agg * c= malloc(sizeof(agg));
	c->b=malloc(sizeof(MonitorBuffer));//ho bisogno di allocare dinamicamente anche i campi della struct condivisa
	c->v=malloc(sizeof(MonitorVettore));

	pthread_mutex_init(&c->v->mutex, NULL);
	pthread_cond_init(&c->v->produttore, NULL);
	pthread_cond_init(&c->v->consumatore, NULL);

	pthread_mutex_init(&c->b->mutex, NULL);
	pthread_cond_init(&c->b->scrittore, NULL);
	pthread_cond_init(&c->b->lettore, NULL);

	c->v->testa=0;
	c->v->coda=0;
	c->v->contatore=0;

	c->b->num_scrittori=0;
	c->b->num_lettori=0;

	pthread_attr_init(&attr);

	//creazione thread
	int k;
	for(k=0;k<5;k++){
		if(k==0){
			printf("sono il thread generatore %d\n", k);
			pthread_create(&threads[k], &attr, generatore, (void *) c);
		}else if(k==1){
			printf("sono il thread aggiornatore %d\n", k);
			pthread_create(&threads[k], &attr, aggiornatore, (void *)c);
		}else{
			printf("sono il thread destinatario %d\n", k);
			pthread_create(&threads[k], &attr, destinatario, (void*)c);
		}
	}
//join thread
for(k=0;k<5;k++){
	pthread_join(threads[k], NULL);
	printf("thread numero %d terminato\n", k);
}


//destroy attr
pthread_attr_destroy(&attr);
//destroy mutex
pthread_mutex_destroy(&c->v->mutex);
        pthread_cond_destroy(&c->v->produttore);
        pthread_cond_destroy(&c->v->consumatore);

        pthread_mutex_destroy(&c->b->mutex);
        pthread_cond_destroy(&c->b->scrittore);
        pthread_cond_destroy(&c->b->lettore);

//liberazione memoria heap
free(c);
//pthread_exit
pthread_exit(0);
}

