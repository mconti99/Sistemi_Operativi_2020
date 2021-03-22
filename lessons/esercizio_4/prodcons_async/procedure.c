#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "header.h"
#include <time.h>

void produttore(int queue, char * text){
	messaggio m;
	//costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	strcpy(m.mess, text);
	//invio messaggio
	msgsnd(queue, &m, sizeof(messaggio)-sizeof(long), IPC_NOWAIT);
	printf("Messaggio inviato: <%s>\n", m.mess);
}

void consumatore(int queue){
	messaggio m;
	//ricezione messaggio
	msgrcv(queue, &m, sizeof(messaggio)-sizeof(long), MESSAGGIO, 0);
	printf("MESSAGGIO RICEVUTO: <%s>\n", m.mess);
	printmsginfo(queue);
}

void printmsginfo(int queue){
	struct msqid_ds mid;
	msgctl(queue, IPC_STAT, &mid);
	char * time_sender= ctime(&mid.msg_stime);
	char * time_receiver = ctime(&mid.msg_rtime);
	char * time_ctime= ctime(&mid.msg_ctime);
	printf("time sender: %s time receiver: %s, time ctime: %s", time_sender, time_receiver, time_ctime);
	printf("Messagges number: %lu\n", mid.msg_qnum);
}
