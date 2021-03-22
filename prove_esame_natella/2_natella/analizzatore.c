#include "procedure.h"

int main(){
        key_t chiave=ftok(FTOK_PATH, FTOK_CHAR);

        int ds_shm =shmget(chiave, sizeof(buffer), IPC_CREAT|0664);

        buffer *p;
        p=shmat(ds_shm, NULL, 0);

        srand(time(NULL));
        key_t chiave1=ftok(FTOK_PATH, FTOK_CHAR1);
        int ds_sem=semget(chiave1, 4, IPC_CREAT|0664);
	while(1){
	analizzatore(ds_sem, p);
	}
	return 0;
}
