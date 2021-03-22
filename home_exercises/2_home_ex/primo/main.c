#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"



int main() {


	key_t chiave = ftok(FTOK_PATH_M1, FTOK_CHAR_M1);

	int ds_shm = shmget(chiave, sizeof(posto)*DIM_BUFFER, IPC_CREAT|0664);

	if(ds_shm<0) { perror("SHM errore"); exit(1); }

	posto  * p;

	p = (posto *) shmat(ds_shm, NULL, 0);
	
	int ds_1 = shmget(IPC_PRIVATE, sizeof(int),IPC_CREAT|0664);

	if(ds_1<0){perror("SHM ERRORE"); exit(1);}

	int * d1;

	d1=(int*) shmat(ds_1, NULL, 0);
	
	*d1=80;
	for(int i=0; i<DIM_BUFFER; i++) {
		p[i].stato = BUFFER_VUOTO;
		p[i].id_cliente =0;
	}



	key_t chiavesem = ftok(FTOK_PATH_M, FTOK_CHAR_M);

	int ds_sem = semget(chiavesem, 2, IPC_CREAT|0664);

	if(ds_sem<0) { perror("SEM errore"); exit(1); }

    //SEMAFORI COMPETIZIONE tra i prod e i cons
	semctl(ds_sem, MUTEX_VETT, SETVAL, 1);
	semctl(ds_sem, MUTEX_VAR, SETVAL, 1);


	for(int i=0; i<NUM_PRODUTTORI; i++) {

		int pid = fork();

		if(pid==0) {

			//figlio produttore

			printf("Inizio figlio produttore  %d\n", i);

			srand(getpid()*time(NULL));

			produttore(p, d1,  ds_sem);

			exit(1);
		}
	}



	for(int i=0; i<NUM_PRODUTTORI; i++) {
		wait(NULL);
		printf("Figlio produttore terminato\n");
	}

        shmctl(ds_shm, IPC_RMID, NULL);
	shmctl(ds_1, IPC_RMID, NULL);
        semctl(ds_sem, 0, IPC_RMID);

        return 0;

}
