#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "header.h"

static int queue1;
static int queue2;

//inizializzazione code di servizio
void initservicequeues(){
	queue1=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	queue2=msgget(IPC_PRIVATE, IPC_CREAT|0664);
}

//rimozione code di servizio
void removeservicequeues(){
	msgctl(queue1, IPC_RMID,0);
	msgctl(queue2, IPC_RMID,0);
}
//send sincrona
void sendsincr(messaggio *m, int queue){
	messaggio m1,m2;
	//costruzione messaggio RTS
	m1.tipo=REQUEST_TO_SEND;
	strcpy(m1.mess, "Richiesta di invio");
	//invio messaggio RTS
	msgsnd(queue1, &m1, sizeof(messaggio)-sizeof(long),0);
	//ricezione OTS
	msgrcv(queue2, &m2, sizeof(messaggio)-sizeof(long), OK_TO_SEND, 0);
	// invio messaggio
	msgsnd(queue, m, sizeof(messaggio)-sizeof(long), 0);
}

//receive bloccante
void receivebloc(messaggio *m, int queue, int tipomess){
	messaggio m1, m2;
	//ricezione messaggio RTS
	msgrcv(queue1, &m1, sizeof(messaggio)-sizeof(long), REQUEST_TO_SEND,0);
	//costruzione MESSAGGIO OTS
	m2.tipo=OK_TO_SEND;
	strcpy(m2.mess, "Ready to send");
	//invio messaggio OTS
	msgsnd(queue2, &m2, sizeof(messaggio)-sizeof(long), 0);
	// ricezione messaggio
	msgrcv(queue, m, sizeof(messaggio)-sizeof(long), tipomess, 0);
}

void produttore(int queue, char* text){
	messaggio m;
	//costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	strcpy(m.mess, text);
	// invio messaggio
	sendsincr(&m, queue);
	printf("MESSAGGIO INVIATO: <%s>\n", m.mess);
}

void consumatore(int queue){
	messaggio m;
	//ricezione messaggio
	receivebloc(&m, queue, MESSAGGIO);
	printf("MESSAGGIO RICEVUTO: <%s>\n", m.mess);
}
