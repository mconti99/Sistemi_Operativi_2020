#include "procedure.h"

int main(){
	key_t chiave= ftok(FTOK_PATH, FTOK_CHAR);
        int ds_shm =shmget(chiave, sizeof(BufferCircolare), IPC_CREAT|0664);
	srand(time(NULL));
        BufferCircolare *p;
        p=shmat(ds_shm, NULL, 0);	
	srand(time(NULL)*getpid());
        key_t chiave1=ftok(FTOK_PATH, FTOK_CHAR1);
        int ds_sem=semget(chiave1, 3, IPC_CREAT|0664);
	printf("produttore pronto\n");
	produci_elemento(ds_sem, p);
	printf("produttor esce\n");
	return 0;
}
