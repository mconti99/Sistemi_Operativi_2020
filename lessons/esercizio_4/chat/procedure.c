#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void sender(int id_queue_receiver, int id_queue_sender){
	struct msg mess; 
	int ret;
	while(1){

		//prelevo il messaggio da inviare
		printf("Inserisci il messaggio da inviare [max 20 caratteri]\n");
		scanf("%s", mess.message);

		//setto il tipo
		mess.tipo= TYPE;

		//verifico se il messaggio è exit
		if(strcmp(mess.message, "exit")==0){
			//essendo exit, lo invio sulla seconda coda e termino
			ret=msgsnd(id_queue_receiver, &mess, sizeof(struct msg)-sizeof(long),0);//lo invio sul mio receiver per farmi terminare
			if(ret<0){_exit(1);}
			printf("[SENDER] inviato: %s\n", mess.message);
			_exit(1);
		}else{
			//non essendo exit, lo invio sulla prima coda
			ret=msgsnd(id_queue_sender, &mess, sizeof(struct msg)-sizeof(long),0);
			if(ret<0){_exit(1);}
			printf("[SENDER] inviato: %s\n", mess.message);
		}
	}
}

void receiver(int id_queue_receiver){
	struct msg mess;
	int ret;
	while(1){
		//mi metto in attesa di un messaggio sulla seconda coda
		ret=msgrcv(id_queue_receiver, &mess, sizeof(struct msg)-sizeof(long), TYPE, 0);
		if(ret<0){_exit(1);}
		printf("[RECEIVER] ricevuto: %s\n", mess.message);

		//se il messaggio ricevuto è exit termino
		if(strcmp(mess.message, "exit")==0) _exit(1);
	}
}
