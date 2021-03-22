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
	int i;
	char m[30];
	//assegnazione coda di comunicazione
	queue=msgget(IPC_PRIVATE, IPC_CREAT|0664);

	//generazione produttore e consumatore
	pid=fork();
	if(pid==0){
		//processo figlio produttore
		printf("sono il produttore. il mio pid %d \n", getpid());
		for(i=0;i<10;i++){
			sprintf(m, "stringa %d", i);
			usleep(100);
			produttore(queue, m);
		}
		_exit(0);
	}else{
		pid=fork();
		//genera il secondo figlio consumatore
		if(pid==0){
			printf("sono il figlio consumatore. il mio pid %d \n", getpid());
			sleep(1);
			for(i=0;i<10;i++){
				consumatore(queue);
			}
			_exit(0);
		}
	}

	//attesa di terminazione
	for(k=0;k<2;k++){//ho solo 2 processi
		pid=wait(&status);
		if(pid==-1) perror("errore");
		else printf("figio numero %d è morto con status =%d\n", pid, status>>8);
	}

	//dealloco struttura
	msgctl(queue, IPC_RMID, 0);
	return 0;

}
