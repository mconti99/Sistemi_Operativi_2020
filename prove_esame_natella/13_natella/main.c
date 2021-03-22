#include "header.h"

int main(){
	int ds_shm=shmget(IPC_PRIVATE, sizeof(struttura), IPC_CREAT|0664);
	struttura * s= shmat(ds_shm, 0, 0);
	int ds_sem=semget(IPC_PRIVATE, 5, IPC_CREAT|0664);
	semctl(ds_sem, 0, SETVAL, 0);
	semctl(ds_sem, 1, SETVAL, 0);
	semctl(ds_sem, 2, SETVAL, 0);
	semctl(ds_sem, 3, SETVAL, 1);
	semctl(ds_sem, 4, SETVAL, 1);

	pid_t pid;
	for(int i=0;i<3;i++){
		pid=fork();
		if(pid==0){
			buffer b;
			b.valore=rand()%10;
			b.chiave=i+1;
			produci(ds_sem, s, b);
		        exit(0);
		}
	}
	
	for(int i=0;i<3;i++){
		pid=fork();
		if(pid==0){
			buffer * b;
			consuma(ds_sem, s, i, b);
			exit(0);
		}
	}

	for(int i=0;i<6;i++) wait(NULL);

	semctl(ds_sem, 0, IPC_RMID);
	shmctl(ds_shm, IPC_RMID, 0);
		
	return 0;
}
