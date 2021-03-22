#include "procedure.h"
#include "semafori.h"

void produci_elemento(int sem_id, BufferCircolare* buf){
	int i=rand()%11;
	Wait_Sem(sem_id, SPAZIO_DISPONIBILE);
	Wait_Sem(sem_id, MUTEX);
	buf->elementi[buf->testa]=i;
	buf->testa=(buf->testa+1)%N;
	buf->riemp++;
	printf("elemento prodotto, numero attuale: %d\n", buf->riemp);
	

	if(buf->riemp==N){
		printf("buffer pieno\n");
		Signal_Sem(sem_id, MESSAGGIO_DISPONIBILE);
	}
	Signal_Sem(sem_id,MUTEX);
}
void consuma_elementi(int sem_id, BufferCircolare* buf){
	int somma;
	printf("consumatore: aspetto\n");
	Wait_Sem(sem_id, MESSAGGIO_DISPONIBILE);
	//non serve un mutex per i consumatori perchè è solo 1
	for(int i=0;i<buf->riemp;i++){
	printf("sto consumando il valore %d: %d", i, buf->elementi[i]);
	}
	for(int i=0;i<buf->riemp;i++) {
		 somma += buf->elementi[i];
	}
	float media=somma/buf->riemp;
	printf("la media è %f", media);
	float x;
	for(int i=0;i<buf->riemp;i++){
		x += pow((buf->elementi[i])-media,2);
	}

	float y=x/4;
	float z=sqrt(y);
	buf->riemp=0;
	buf->testa=0;
	buf->coda=0;
	for(int i=0;i<N;i++)
	Signal_Sem(sem_id, SPAZIO_DISPONIBILE);
}
