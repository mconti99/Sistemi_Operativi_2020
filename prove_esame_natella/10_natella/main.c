#include "header.h"
int coda_richieste1, coda_richieste2, coda_risposte;

int main(){
	coda_richieste1=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	coda_richieste2=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	coda_risposte=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	init(); //MERDA
	pthread_attr_t attr;
	monitor* m=malloc(sizeof(monitor));
	
	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->consumatori, NULL);
	
	m->testa=0;
m->coda=0;
m->contatore=0;

pthread_attr_init(&attr);
pid_t pid;
for(int i=0;i<3;i++){
	pid=fork();
	if(pid==0){
		srand(getpid()*time(NULL));
		client();
		exit(0);
	}
}

	pthread_t cons;
	pthread_t prod;
	pthread_create(&prod, &attr, produttore, (void*)m);
	pthread_create(&cons, &attr, consumatore, (void*)m);
	
	pid=fork();
	if(pid==0){
		server();
		exit(0);
	}

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	for(int i=0;i<4;i++) wait(NULL);

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->consumatori);
	
	free(m);
	msgctl(coda_richieste1, IPC_RMID, 0);
	msgctl(coda_richieste2, IPC_RMID, 0);
	msgctl(coda_risposte, IPC_RMID, 0);

	pthread_exit(0);

	return 0;
}
