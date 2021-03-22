#include "header.h"

void genera(MonitorVettore *v, elemento e){
	pthread_mutex_lock(&v->mutex);
	while(v->contatore==5){
		pthread_cond_wait(&v->produttore, &v->mutex);
	}
	v->vettore[v->coda]=e;
	printf("GENERATORE: elemento 1: %d, elemento 2: %d\n", v->vettore[v->coda].a, v->vettore[v->coda].b);
	v->coda=(v->coda+1)%5;
	v->contatore++;
	pthread_cond_signal(&v->consumatore);
	pthread_mutex_unlock(&v->mutex);
}
elemento preleva(MonitorVettore *v){
	elemento e;
	pthread_mutex_lock(&v->mutex);
	while(v->contatore==0){
		pthread_cond_wait(&v->consumatore, &v->mutex);
	}
	e=v->vettore[v->testa];
	printf("AGGIORNATORE: elemento1: %d, elemento 2: %d\n", e.a, e.b);
	v->testa=(v->testa+1)%5;
	v->contatore--;
	pthread_cond_signal(&v->produttore);
	pthread_mutex_unlock(&v->mutex);
	return e;
}	
void aggiorna(MonitorBuffer *v, elemento e){
	pthread_mutex_lock(&v->mutex);
	while(v->num_lettori>0){
		pthread_cond_wait(&v->scrittore, &v->mutex);
	}
	v->num_scrittori++;
	pthread_mutex_unlock(&v->mutex);
	v->buffer=e;
	pthread_mutex_lock(&v->mutex);
	v->num_scrittori--;
	pthread_cond_broadcast(&v->lettore);
	pthread_mutex_unlock(&v->mutex);
}
void consulta(MonitorBuffer *v){
	elemento e;
	pthread_mutex_lock(&v->mutex);
	while(v->num_scrittori>0){
		pthread_cond_wait(&v->lettore, &v->mutex);
	}
	v->num_lettori++;
	pthread_mutex_unlock(&v->mutex);
	e=v->buffer;
	printf("DESTINATARIO: elemento 1: %d, elemento 2: %d, somma: %d\n", e.a, e.b, e.a+e.b);
	pthread_mutex_lock(&v->mutex);
	v->num_lettori--;
	if(v->num_lettori==0) pthread_cond_signal(&v->scrittore);
	pthread_mutex_unlock(&v->mutex);
}

void * generatore(void * v){
	agg * p=(agg * )v;
	srand(time(NULL));
	elemento e;
	for(int i=0;i<10;i++){
	e.a=rand()%11;
	e.b=rand()%11;
	genera(p->v, e);
	}
	pthread_exit(0);
}

void * aggiornatore(void * m){
	agg * p= (agg *) m;
	elemento e;
	for(int i=0;i<10;i++){
		e=preleva(p->v);
		aggiorna(p->b, e);
		sleep(1);
	}
	pthread_exit(0);
}

void * destinatario(void * v){
	agg * p=(agg *) v;
	for(int i=0;i<6;i++){
		consulta(p->b);
		sleep(2);
	}
	pthread_exit(0);
}
