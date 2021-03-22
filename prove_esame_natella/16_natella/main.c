#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

int main() {

	int msg_id_balancer;
	int msg_id_server[TOTALE_SERVER];
	int i;
	pid_t p;
	int status;
	int ret;



	/*
	  TBD: Creare una coda per i messaggi dai client
	  verso il balancer
	*/
	
	msg_id_balancer = msgget(IPC_PRIVATE, IPC_CREAT|0664);

	if(msg_id_balancer < 0) {

		perror("Errore msgget() coda balancer");
		exit(1);
	}

	msg_id_server[0]=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	msg_id_server[1]=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	msg_id_server[2]=msgget(IPC_PRIVATE, IPC_CREAT|0664);

	/*
	  TBD: Creare 3 code per i messaggi dal balancer verso
	  i server, una coda per ogni server
	*/




	/*
	  TBD: Creare i processi client, passando alla funzione Client()
	  in ingresso lo ID della coda del balancer
	*/
	pid_t pid;
	for(i=0; i<TOTALE_CLIENT; i++) {

		pid=fork();
		if(pid==0){
			Client(msg_id_balancer);
			exit(0);
		}
	}



	/*
	  TBD: Creare i processi server, passando alla funzione Server()
	  in ingresso lo ID della coda di quel server
	*/

	for(i=0; i<TOTALE_SERVER; i++) {

		pid=fork();
		if(pid==0){
			Server(msg_id_server[i]);
			exit(0);
		}
	}



	/*
	  TBD: Creare il processo balancer, passando alla funzione Balancer()
	in ingresso gli ID di tutte le code
	*/
	pid=fork();
	if(pid==0){
		Balancer(msg_id_balancer, msg_id_server);
		exit(0);
	}



	/*
	  TBD: Il processo padre si pone in attesa della terminazione
	  di tutti i processi (client, server e balancer)
	*/

	for(i=0; i<TOTALE_CLIENT+TOTALE_SERVER+1; i++) {

		wait(NULL);
	}



	/*
	  TBD: Rimozione delle code dal sistema
	*/
	msgctl(msg_id_balancer, IPC_RMID, 0);
	msgctl(msg_id_server[0], IPC_RMID, 0);
	msgctl(msg_id_server[1], IPC_RMID, 0);
	msgctl(msg_id_server[2], IPC_RMID, 0);
	return 0;

}
