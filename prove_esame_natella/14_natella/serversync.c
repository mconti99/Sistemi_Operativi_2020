#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "serversync.h"



void send_sinc(int ok_id, int req_id, messaggio * msg)
{

    int ret;

    msgRTS m1;
 	m1.typeRTS=1;
	m1.pid=getpid();


    printf("[%d] Client: invio request-to-send, type=%ld\n", getpid(), m1.typeRTS);

    ret = msgsnd(req_id, &m1, sizeof(msgRTS)-sizeof(long), 0);

    if (ret < 0)
    {
        perror("Errore msgsnd (request-to-send)");
        exit(1);
    }


    msgOTS m2;

    printf("[%d] Client: in attesa di ok-to-send...\n", getpid());

    ret = msgrcv(ok_id, &m2, sizeof(msgOTS)-sizeof(long), getpid(), 0);

    if (ret < 0)
    {
        perror("Errore msgrcv (ok-to-send)");
        exit(1);
    }

    printf("[%d] Client: ricevuto ok-to-send... type=%ld, id_coda=%d\n", getpid(), m2.pid, m2.ID);




	
    int id_coda = m2.ID;

    printf("[%d] Client: invio messaggio, coda=%d, type=%ld, valore=%d\n", getpid(), id_coda, msg->type, msg->val);

    ret = msgsnd(id_coda, msg, sizeof(messaggio)-sizeof(long), 0);

    if (ret < 0)
    {
        perror("Errore msgsnd (coda messaggi)");
        exit(1);
    }

}

void receive_sinc(int msg_id, int ok_id, int req_id, messaggio * msg)
{

    int ret;


    /* TBD: Ricevere il messaggio REQUEST TO SEND */
    msgRTS m1;

    printf("[%d] Server: in attesa di request-to-send...\n", getpid());

    ret = msgrcv(req_id, &m1, sizeof(msgRTS)-sizeof(long), RTS, 0);

    printf("[%d] Server: ricevuto request-to-send, type=%ld\n", getpid(), m1.typeRTS);

    if (ret < 0)
    {
        perror("Errore msgrcv (request-to-send)");
        exit(1);
    }



    /* TBD: Inviare il messaggio OK TO SEND */
	msgOTS m2;
	m2.pid=m1.pid;
	m2.ID=msg_id;
    printf("[%d] Server: invio ok-to-send, type=%ld, id_coda=%d\n", getpid(), m2.pid, m2.ID);

    ret = msgsnd(ok_id, &m2, sizeof(msgOTS)-sizeof(long), 0);

    if (ret < 0)
    {
        perror("Errore msgsnd (ok-to-send)");
        exit(1);
    }



    /* TBD: Ricevere il messaggio destinato al server, usando la struct indicata
            dal puntatore "msg" (passato dal chiamante della funzione) 
     */

    printf("[%d] Server: in attesa del messaggio...\n", getpid());

    ret = msgrcv(msg_id, msg, sizeof(messaggio)-sizeof(long), MSG, 0);

    if (ret < 0)
    {
        perror("Errore msgrcv (coda messaggi)");
        exit(1);
    }

    printf("[%d] Server: ricevuto messaggio, type=%ld, valore=%d\n", getpid(), msg->type, msg->val);

}
