#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include "header.h"

void produci(struct ProdCons* pc, msg m){
	//per i monitor era: enter monitor -> enter_monitor(rif_mon)
	pthread_mutex_lock(&pc->mutex);

	while(pc->ok_produzione==0){ //SIGNAL AND CONTINUE
		pthread_cond_wait(&pc->ok_prod_cv, &pc->mutex);
	}


	//prod
	pc->mess=m;
	
	//update var cond
	pc->ok_produzione=0;
	pc->ok_consumo=1;
	//signal i consumatori
	pthread_cond_signal(&pc->ok_cons_cv);
	//leave monitor
	pthread_mutex_unlock(&pc->mutex);

}
void consuma(struct ProdCons *pc, msg m){
	
	pthread_mutex_lock(&pc->mutex);//entro nel monitor
	while(pc->ok_consumo==0){
		pthread_cond_wait(&pc->ok_cons_cv, &pc->mutex);//non posso consumare
	}
	//consumo il messaggio
	printf("valore consumato: %ld\n", pc->mess);
	pc->ok_produzione=1;
	pc->ok_consumo=0;

	pthread_cond_signal(&pc->ok_prod_cv);//segnalo i produttori
	pthread_mutex_unlock(&pc->mutex);

}
void * produttore(void * p){
	struct ProdCons * pc=(struct ProdCons *)p; //DA FARE ogni volta che uso una struct nei PTHREAD
	int i;
	for(i=0;i<3;i++){
		struct timeval t1;
		struct timezone t2;

		gettimeofday(&t1, &t2);

		msg m=t1.tv_usec;
		printf("messaggio prodotto: %ld\n", m);
		produci(pc, m);
	}
	pthread_exit(0);
}
void * consumatore(void * p){
	struct ProdCons *pc=(struct ProdCons*)p;
		for(int i=0;i<3;i++){
			msg m;
			consuma(pc,m);
		}
	pthread_exit(0);
}
