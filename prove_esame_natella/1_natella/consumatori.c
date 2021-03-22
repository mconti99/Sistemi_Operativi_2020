#include "procedure.h"

int main(){

		key_t chiave= ftok(FTOK_PATH, FTOK_CHAR);
        int ds_shm =shmget(chiave, sizeof(BufferCircolare), IPC_CREAT|0664);
        BufferCircolare *p;
        p=shmat(ds_shm, NULL, 0);
        key_t chiave1=ftok(FTOK_PATH, FTOK_CHAR1);
        int ds_sem=semget(chiave1, 3, IPC_CREAT|0664);
        
	printf("ci sto");
       	consuma_elementi(ds_sem, p);
		//sleep(1);
		consuma_elementi(ds_sem, p);
	return 0;
}
