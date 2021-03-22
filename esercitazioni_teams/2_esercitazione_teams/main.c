#include "header.h"

int main(){
	int coda_gen;
	int coda_filtro;
	int coda_csum;
	coda_gen=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	if(coda_gen<0){perror("errore msgget"); exit(1);}
	coda_filtro=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	if(coda_filtro<0){perror("errore msgget"); exit(1);}
	coda_csum=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	if(coda_csum<0){perror("errore msgget"); exit(1);}
	
	pid_t pid;
	for(int i=0;i<3;i++){
		pid=fork();
		if(pid==0){
			srand(time(NULL)*getpid());
			printf("sono il generatore numero %d con pid %d\n", i, getpid());
			generatore(coda_gen, i);
			exit(0);
		}
		else if(pid<0){
			perror("errore fork");
			exit(1);
		}
	}

	pid=fork();
	if(pid==0){
		printf("sono il filtro\n");
		filtro(coda_gen, coda_filtro);
                exit(0);
	}else if(pid<0){
		perror("errore fork");
		exit(1);
	}

	pid=fork();
	if(pid==0){
		printf("sono il processo checksum\n");
		checksum(coda_filtro, coda_csum);
		exit(0);
	}else if(pid<0){
		perror("errore fork");
		exit(1);
	}

	pid=fork();
	if(pid==0){
		printf("sono il processo visualizzatore\n");
		visualizzatore(coda_csum);
		exit(0);
	}else if(pid<0){
		perror("errore fork");
		exit(1);
	}

	for(int i=0;i<6;i++) wait(NULL);
	msgctl(coda_gen, IPC_RMID, 0);
	msgctl(coda_filtro, IPC_RMID, 0);
	msgctl(coda_csum, IPC_RMID, 0);
	return 0;
}
