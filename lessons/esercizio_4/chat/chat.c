#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main(int argc, char* argv[]){
	pid_t pid;
	int i;

	//controllo gli argomenti passati
	if(argc<2){
		printf("Errore: fornire come parametri di ingresso 2 caratteri separati da spazio\n");
		printf("Esempio: %s a b \n", argv[0]);
		_exit(1);
	}

	char firstchar = * argv[1];
	char secondchar = *argv[2];
	
	printf("i caratteri inseriti sono %c %c\n", firstchar, secondchar);

	//creo le chiave per le due code di messaggi
	key_t queue_sender=ftok(FTOK_PATH, firstchar);
	key_t queue_receiver=ftok(FTOK_PATH, secondchar);

	//creo le due code
	int id_queue_sender=msgget(queue_sender, IPC_CREAT|0644);

	if(id_queue_sender<0){perror("msgget fallita"); exit(1);}

	int id_queue_receiver=msgget(queue_receiver, IPC_CREAT|0644);
	if(id_queue_receiver<0){perror("msgget fallita");exit(1);}

	//genero i due figli
	for(i=0;i<2;i++){
		pid=fork();
		if(pid==0){
			if(i==0) //sender
				sender(id_queue_receiver, id_queue_sender);
			else //receiver
				receiver(id_queue_receiver);
		}else if(pid<0){perror("fork fallita"); exit(1);}
	}
	
	//attendo che i figli, mittente e destinatario, siano terminati
	for(i=0;i<2;i++){
		wait(NULL);
	}

	//rimuovo le code
	msgctl(id_queue_sender, IPC_RMID, 0);
	msgctl(id_queue_receiver, IPC_RMID, 0);
}
