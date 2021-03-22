#include "procedure.h"

int main(){
	key_t chiave= ftok(FTOK_PATH, FTOK_CHAR);
	int ds_shm =shmget(chiave, sizeof(BufferCircolare), IPC_CREAT|0664);

	BufferCircolare *p;
	p=shmat(ds_shm, NULL, 0);
	p->testa=0;
	p->coda=0;
	p->riemp=0;
	key_t chiave1=ftok(FTOK_PATH, FTOK_CHAR1);
	int ds_sem=semget(chiave1, 3, IPC_CREAT|0664);

	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, N);
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
	semctl(ds_sem, MUTEX, SETVAL, 1);
	
	pid_t pid=fork();
	sleep((rand()%3)+1);
	if(pid==0){
		printf("creo consumatore\n");
		execl("./consumatori","consumatori", NULL);

		printf("errore execl consumatori\n");
		return -1;
	}
	
	for(int i=0;i<10;i++){
	//sleep((rand()%3)+1);
	pid=fork();
	if(pid==0){
	       	printf("creo produttore %d\n", i);
		execl("./produttori", "produttori", NULL);
		
		printf("errore execl produttori\n");
		return -1;
	}
	for(int i=0;i<11;i++){
		wait(NULL);
	}
	shmctl(ds_shm, IPC_RMID, 0);
	semctl(ds_sem, 0,IPC_RMID);
	return 0;
}
}
