#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    buf1_id = shmget(k1, sizeof(buffer), IPC_CREAT|0664);/* TBD: Acquisizione shared memory buffer singolo */

    if (buf1_id < 0)
    {
        perror("Errore accesso SHM buf1");
        exit(1);
    }

    buf2_id = shmget(k2, sizeof(buffer), IPC_CREAT|0664);/* TBD: Acquisizione shared memory buffer singolo */

    if (buf2_id < 0)
    {
        perror("Errore accesso SHM buf2");
        exit(1);
    }

    sem_id = semget(k3,2, IPC_CREAT|0664);/* TBD: Acquisizione vettore semafori */

    if (sem_id < 0)
    {
        perror("Errore accesso semafori");
        exit(1);
    }

    buf1 = shmat(buf1_id, 0,0);/* TBD: Attach shared memory */

    if (buf1 == (void *)-1)
    {
        perror("Errore attach SHM buf1");
        exit(1);
    }

    buf2 = shmat(buf2_id, 0, 0);/* TBD: Attach shared memory */

    if (buf2 == (void *)-1)
    {
        perror("Errore attach SHM buf2");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < 5; i++)
    {

        int valore = rand() % 10;

        produzione(sem_id, buf1, buf2, valore);
    }

    exit(0);
}
