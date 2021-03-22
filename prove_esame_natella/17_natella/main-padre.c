#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "buffer.h"

int main()
{

    int buf1_id;
    int buf2_id;
    buffer *buf1;
    buffer *buf2;
    int sem_id;
	key_t k1, k2, k3;
	k1=ftok(".", 'a');
	k2=ftok(".", 'b');
	k3=ftok(".", 'c');
    buf1_id = shmget(k1, sizeof(buffer), IPC_CREAT|0664);/* TBD: Creazione shared memory buffer singolo */

    if (buf1_id < 0)
    {
        perror("Errore creazione SHM buf1");
        exit(1);
    }

    buf2_id = shmget(k2, sizeof(buffer), IPC_CREAT|0664);/* TBD: Creazione shared memory buffer singolo */

    if (buf2_id < 0)
    {
        perror("Errore creazione SHM buf2");
        exit(1);
    }

    sem_id = semget(k3,2, IPC_CREAT|0664); /* TBD: Creazione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore creazione semafori");
        exit(1);
    }

    buf1 = shmat(buf1_id, 0,0); /* TBD: Attach shared memory buffer singolo */

    if (buf1 == (void *)-1)
    {
        perror("Errore attach SHM buf1");
        exit(1);
    }

    buf2 =shmat(buf2_id, 0, 0); /* TBD: Attach shared memory buffer singolo */

    if (buf2 == (void *)-1)
    {
        perror("Errore attach SHM buf2");
        exit(1);
    }

    /* TBD: inizializzazione stato buf1 e buf2 */
	buf1->stato=LIBERO;
	buf2->stato=LIBERO;
    /* TBD: inizializzazione semafori */
	semctl(sem_id, 0, SETVAL, 1);
	semctl(sem_id, 1, SETVAL, 0);

    /* TBD: Creazione processo produttore */
    	pid_t pid;
	pid=fork();
	if(pid==0){
		execl("./main-consumatore", "main-consumatore", (char*) 0);
	}
    /* TBD: Creazione processo consumatore */
	pid=fork();
	if(pid==0){
		execl("./main-produttore", "main-produttore", (char*) 0);
	

	}
    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }

    shmctl(buf1_id, IPC_RMID, NULL);
    shmctl(buf2_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
}
