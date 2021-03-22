#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "serversync.h"

int main()
{

    /* Coda "OK TO SEND" */

    key_t ok_key = ftok(".", 'a');/* TBD: Definire una chiave per "OK TO SEND" */

    int ok_id =  msgget(ok_key, IPC_CREAT|0664);/* TBD: Ottenere la coda per i messaggi "OK TO SEND" */

    if (ok_id < 0)
    {
        perror("Errore creazione coda ok-to-send");
        exit(1);
    }

    /* Coda "REQUEST TO SEND" */

    key_t req_key = ftok(".", 'b');/* TBD: Definire una chiave per "REQUEST TO SEND" */

    int req_id = msgget(req_key, IPC_CREAT|0664);/* TBD: Ottenere la coda per i messaggi "REQUEST TO SEND" */

    if (req_id < 0)
    {
        perror("Errore creazione coda request-to-send");
        exit(1);
    }




    srand(getpid());

    for (int i = 0; i < 2; i++)
    {
        int val = rand() % 100;

        printf("[%d] Client: invio val=%d\n", getpid(), val);
	
	messaggio msg;
	msg.val=val;
	msg.type=2;
	send_sinc(ok_id, req_id, &msg);
        /* TBD: Inviare un messaggio al server, usando la struct "messaggio"
                definita in "serversync.h" 
         */

        /* NOTA: sarà la funzione send_sinc() a scambiare i messaggi 
                 "REQUEST TO SEND" e "OK TO SEND" con uno dei server.
        */

        sleep(2);
    }

    return 0;
}
