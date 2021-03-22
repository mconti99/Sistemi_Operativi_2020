#include "procedure.h"

int main(){

	int ds_shm=shmget(IPC_PRIVATE, sizeof(coda), IPC_CREAT|0664);
	coda * c=shmat(ds_shm, 0,0);

	c->contatore=0;
	c->testa=0;
	c->coda=0;
	
	init_monitor(&(c->m), 2);
	srand(time(NULL));
	pid_t pid;
	for(int i=0;i<5;i++){
		pid=fork();
		if(pid==0){
			printf("sono l'utente con pid %d\n", getpid());
			for(int j=0;j<5;j++){
				printf("produco %d\n", j);
				produci(c);
			}
			exit(0);
		}
		else if(pid<0){
			perror("errore fork");
			exit(1);
		}
	}

	
	pid=fork();
	if(pid==0){
		printf("sono lo schedulatore\n");
		pid_t disco[20];
		for(int i=0;i<20;i++) disco[i]=0;
		int posizione_corrente=0;
		richiesta r;
		for(int i=0;i<25;i++){
		printf("consumo %d\n", i);
		consuma(c,&r);
                printf("posizione: %d\n", r.posizione);
		sleep(abs((int)r.posizione-posizione_corrente));
		posizione_corrente=r.posizione;
		disco[posizione_corrente]=r.processo;
		printf("DISCO: ");
		for(int z=0;z<20;z++){
			printf(" [%d] ", disco[z]);
		}
		printf("\n");
	}
		exit(0);
	}
	for(int i=0;i<6;i++) wait(NULL);

	remove_monitor(&(c->m));
	shmctl(ds_shm, IPC_RMID, 0);
	return 0;
}
