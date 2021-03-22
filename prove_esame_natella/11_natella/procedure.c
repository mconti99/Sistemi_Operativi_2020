#include "header.h"
int coda_richieste, coda_risposte;
void client(){
  msg m;
  msg1 m1;
	m.pid=getpid();
      for(int i=0;i<5;i++){
 	m.valore1=rand()%11;
	m.valore2=rand()%11;
	msgsnd(coda_richieste, &m, sizeof(msg)-sizeof(long), 0);
	msgrcv(coda_risposte, &m1, sizeof(msg1)-sizeof(long), getpid(), 0);
	printf("CLIENT: messaggio ricevuto dal server [%d] [%ld]\n", m1.prod, m1.pid);
} 

void * manager(void * p){
	int ret;
	msg m;
	struttura * c = (struttura*) p;
	while(1){
	while(ret==-1){
		ret=msgrcv(coda_richieste, &m, sizeof(msg)-sizeof(long),0, IPC_NOWAIT);
		sleep(1);
	}
	pthread_mutex_lock(&c->mutex);
	while(c->contatore==2){
		pthread_cond_wait(&c->produttori, &m->mutex);	
	}
	c->buffer[c->testa]=m;
	c->testa=(c->testa+1)%2;
	c->contatore++;
	pthread_cond_signal(&c->consumatori);
	pthread_mutex_unlock(&c->mutex);
	}	
}

void * worker(void * p){
	
}


