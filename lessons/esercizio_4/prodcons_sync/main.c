#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include "header.h"

int main(){
	int k, status, queue;
	pid_t pid;

	//assegnazione coda di comunicazione
	queue=msgget(IPC_PRIVATE, IPC_CREAT|0664);

	//inizializzazione code di servizio
	initservicequeues();

	//generazione produttore e consumatore
	pid=fork();
	if(pid==0){
		printf("sono il produttore. il mio pid %d \n", getpid());
		sleep(2);
		produttore(queue,"www.unina.it");
		_exit(0);
	}else{
		pid=fork();
		if(pid==0){
			printf("sono il figlio consumatore. il mio pid %d \n", getpid());
			sleep(1);
			consumatore(queue);
			_exit(0);
		}
	}

	// attesa di terminazione
	for(k=0;k<2;k++){
		pid=wait(&status);
		if(pid==-1) perror("errore");
		else printf("figlio numero %d è morto con status = %d\n", pid, status>>8);
	}
	//deallocazione code
	
	msgctl(queue, IPC_RMID, 0);
	removeservicequeues();
	
	return 0;
}
