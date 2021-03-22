#include "header.h"

int main(){
	int ds_shm=shmget(IPC_PRIVATE, sizeof(struct MonitorLettScritt), IPC_CREAT|0664);

	struct MonitorLettScritt * p=shmat(ds_shm, NULL, 0);
	p->numero_lettori=0;
	p->numero_scrittori=0;
	p->variabile=0;
	p->versione=0;
	pid_t pid;
	init_monitor(&(p->m), 2);
	for(int i=0;i<2;i++){
		pid=fork();
		if(pid==0){
			printf("sono quello che scrivo, numero %d\n", i);
			srand(time(NULL)*getpid());
			for(int j=0;j<10;j++){
				int v=rand()%100;
				printf("CICLO SCRITTURA: scrittura NUMERO %d del PROCESSO %d\n", j, i);
				scrivi(p, v);
				sleep(1);
			}
			exit(0);
		}
	}

	for(int i=0;i<3;i++){
		pid=fork();
		if(pid==0){
			printf("CREAZIONE PROCESSO LETTORE:hey, sono io quello che legge, numero %d\n", i);
			srand(time(NULL)*getpid());
			int z=1+(rand()%3);
			int x;
			x=0;
			for(int j=0;j<5;j++){
				printf("CICLO LETTORE: lettura NUMERO %d del PROCESSO %d\n", j, i);
				leggi(p,&x);
			}
			exit(0);
		}
	}



	for(int i=0;i<5;i++) wait(NULL);
	remove_monitor(&(p->m));
	shmctl(ds_shm, IPC_RMID, 0);
	return 0;
}
