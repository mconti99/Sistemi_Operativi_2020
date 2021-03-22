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
	if(argc<4){
		printf("Errore: fornire come parametri di ingresso 4 caratteri separati da spazio\n");
		printf("Esempio: %s a b c d\n", argv[0]);
		_exit(1);
	}
//nota: creare 4 processi da 4 terminali diversi, con ognuno una sequenza di caratteri in posizione mutuamente eslusiva tra di loro
/* esempio: 
1) ./chat a b c d (ovvero: sender, receiver1, receiver2, receiver3)
2) ./chat b a d c
3) ./chat c d a b
4) ./chat d c b a
*/

	char firstchar = * argv[1];
	char secondchar = *argv[2];
	char thirdchar= *argv[3];
	char quartochar= *argv[4];
	
	printf("i caratteri inseriti sono %c %c %c %c\n", firstchar, secondchar, thirdchar, quartochar);

	//creo le chiave per le due 4 di messaggi
	key_t queue_sender=ftok(FTOK_PATH, firstchar);
	key_t queue_receiver1=ftok(FTOK_PATH, secondchar);
	key_t queue_receiver2=ftok(FTOK_PATH, thirdchar);
	key_t queue_receiver3=ftok(FTOK_PATH, quartochar);

	//creo le 4 code
	int id_queue_sender=msgget(queue_sender, IPC_CREAT|0644);

	if(id_queue_sender<0){perror("msgget fallita"); exit(1);}

	int id_queue_receiver1=msgget(queue_receiver1, IPC_CREAT|0644);
	if(id_queue_receiver1<0){perror("msgget fallita");exit(1);}

	int id_queue_receiver2=msgget(queue_receiver2, IPC_CREAT|0644);
        if(id_queue_receiver2<0){perror("msgget fallita");exit(1);}

	int id_queue_receiver3=msgget(queue_receiver3, IPC_CREAT|0644);
        if(id_queue_receiver3<0){perror("msgget fallita");exit(1);}



	//genero i 4 figli
	for(i=0;i<4;i++){
		pid=fork();
		if(pid==0){
			if(i==0) //sender
				sender(id_queue_receiver1, id_queue_receiver2, id_queue_receiver3, id_queue_sender);
			else if(i==1)
				receiver(id_queue_receiver1);
			else if(i==2)
				receiver(id_queue_receiver2);
			else if(i==3)
				receiver(id_queue_receiver3);

		}else if(pid<0){perror("fork fallita"); exit(1);}
	}
	
	//attendo che i figli siano terminati
	for(i=0;i<4;i++){
		wait(NULL);
	}

	//rimuovo le code
	msgctl(id_queue_sender, IPC_RMID, 0);
	msgctl(id_queue_receiver1, IPC_RMID, 0);
	msgctl(id_queue_receiver2, IPC_RMID, 0);
	msgctl(id_queue_receiver3, IPC_RMID, 0);
}
