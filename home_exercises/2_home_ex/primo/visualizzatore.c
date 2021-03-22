#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


int main(){
	key_t chiave_shm =ftok(FTOK_PATH_M1, FTOK_CHAR_M1);

	int ds_shm = shmget(chiave_shm, sizeof(posto), IPC_CREAT|0664);

	if(ds_shm<0) { perror("SHM errore"); exit(1); }

	posto * p;

	p = (posto *) shmat(ds_shm, NULL, 0);

	while(1){
	sleep(1);	
	for(int i=0;i<DIM_BUFFER;i++){
                 printf("numero di posto: %d ---> stato: %d -----> cliente: %d\n", i, p[i].stato, p[i].id_cliente);
                }
	}
	shmctl(ds_shm, IPC_RMID, NULL);

	return 0;
}

