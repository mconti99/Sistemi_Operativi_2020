#include "header.h"

int main(){
	int ds_shm=shmget(IPC_PRIVATE, sizeof(prodcons), IPC_CREAT|0664);

	prodcons * p=shmat(ds_shm, 0, 0);
	init_monitor(&(p->m), 2);

	pid_t pid;
	for(int i=0;i<5;i++){
		pid=fork();
		if(pid==0){
			srand(time(NULL)*getpid());
			for(int j=0;j<6;j++){
				int valore=rand()%10;
				produci(p, valore);
				sleep(2);
			}
			exit(0);
		}
	}

	for(int i=0;i<5;i++){
		pid=fork();
		if(pid==0){
			for(int j=0;j<3;j++){
				consuma(p);
				sleep(1);
			}
			exit(0);
		}
	}

	for(int i=0;i<10;i++) wait(NULL);
remove_monitor(&(p->m));
shmctl(ds_shm, IPC_RMID, 0);
	return 0;
}
