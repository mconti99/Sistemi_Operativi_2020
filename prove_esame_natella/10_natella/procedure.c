#include "header.h"

int coda_richieste1, coda_richieste2, coda_risposte;
int coda_RTS;
int coda_OTS;

void init(){
	coda_RTS=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	coda_OTS=msgget(IPC_PRIVATE, IPC_CREAT|0664);
}

void removeCodeServizio(){
	msgctl(coda_RTS, IPC_RMID, 0);
	msgctl(coda_OTS, IPC_RMID, 0);
}

void client(){
	msg m, m1;
	m.pid=getpid();
	for(int i=0;i<3;i++){
		m.valore=rand()%101;
		msgsnd(coda_richieste1, &m, sizeof(msg)-sizeof(long), 0);
		printf("CLIENT: ho sendato un messaggio di valore %d e tipo %ld\n", m.valore, m.pid);
		msgrcv(coda_risposte, &m1, sizeof(msg)-sizeof(long), getpid(), 0);
		//printf("CLIENT: ho ricevuto un messaggio di ERRORE di valore %d e tipo %ld\n", m1.valore, m1.pid);

	}
}

void * produttore(void * p){
	monitor * c = (monitor *) p;
	msg m;
	while(1){
	msgrcv(coda_richieste1, &m, sizeof(msg)-sizeof(long), 0, 0);
//	printf("INTERFACCIA: ho ricevuto un messaggio di valore %d e tipo %ld\n", m. valore, m.pid);
	int v = m.valore;
	pthread_mutex_lock(&c->mutex);
	if(c->contatore==DIM){
		msgsnd(coda_risposte, &m, sizeof(msg)-sizeof(long), 0);
		printf("INTERFACCIA: MESSAGE LOST\n"); 
	}else{
	msgsnd(coda_risposte, &m, sizeof(msg)-sizeof(long), 0);
	//printf("INTERFACCIA: valore che inserisco nel vettore = %d\n", v);
	c->vettore[c->testa].valore=v;
	c->vettore[c->testa].pid=m.pid;
	c->testa= (c->testa+1)%DIM;
	c->contatore++;
	pthread_cond_signal(&c->consumatori);
	}
	pthread_mutex_unlock(&c->mutex);
	}
}

void * consumatore(void * p){
	monitor * c =(monitor *) p;
	int v=0;
	long pid;
	while(1){
	pthread_mutex_lock(&c->mutex);
	while(c->contatore==0){
		//printf("CONSUMATORE: mi sospendo\n");
		pthread_cond_wait(&c->consumatori, &c->mutex);
		//printf("CONSUMATORE: mi risveglio\n");
	}
	v=c->vettore[c->coda].valore;
	pid=c->vettore[c->coda].pid;
	c->coda=(c->coda+1)%DIM;
	c->contatore--;
	printf("CONSUMATORE: si consuma il valore %d con pid %ld\n", v, pid);
	pthread_mutex_unlock(&c->mutex);
	msg m;
	m.valore=v;
	m.pid=pid;
	msg m1, m2;
	m1.pid=2;
//	printf("%d\n", coda_RTS);
	msgsnd(coda_RTS, &m1, sizeof(msg)-sizeof(long), 0);
	//printf("CONSUMATORE: faccio la REQUEST TO SEND \n");
	//printf("CONSUMATORE: aspetto la OK TO SEND\n");
	msgrcv(coda_OTS, &m2, sizeof(msg)-sizeof(long), 3, 0);
	msgsnd(coda_richieste2, &m, sizeof(msg)-sizeof(long), 0);
	//printf("CONSUMATORE: ho finito la send sincrona al server con valore %d e tipo %ld\n", m.valore, m.pid);
	}
}

void server(){
	msg m, m1, m2;
	m2.pid=3;
	while(1){
	//printf("SERVER: aspetto la REQUEST TO SEND\n");
	msgrcv(coda_RTS, &m1, sizeof(msg)-sizeof(long), 2, 0);
	//printf("SERVER: faccio l'OK TO SEND \n");
	msgsnd(coda_OTS, &m2, sizeof(msg)-sizeof(long), 0);
	//printf("SERVER: aspetto la SEND SINCRONA\n");
	msgrcv(coda_richieste2, &m, sizeof(msg)-sizeof(long), 0,0);
	printf("SERVER: valore: %d e pid: %ld\n", m.valore, m.pid);

	sleep(1);
	}
}




