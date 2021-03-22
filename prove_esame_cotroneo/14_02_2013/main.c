#include "header.h"

int main(){
	key_t key=ftok(".", 'a');
	int id_shm=shmget(key, sizeof(struttura), IPC_CREAT|0664);
	struttura * s = shmat(id_shm ,0, 0);
	key_t key2=ftok(".", 'b');
	int id_sem=semget(key2, 3, IPC_CREAT|0664);

	semctl(id_sem, 0, SETVAL, 1);
	semctl(id_sem, 1, SETVAL, 1);
	semctl(id_sem, 2, SETVAL, 1);

	pid_t pid;
	pid=fork();
	if(pid==0){
		execl("./docente", "docente", (char*)0);
		exit(0);
	}

	for(int i=0;i<10;i++){
		pid=fork();
		if(pid==0){
			execl("./studente", "studente", (char*)0);
			exit(0);
		}
	}
	for(int i=0;i<11;i++) wait(NULL);

	semctl(id_sem, 0, IPC_RMID);
	shmctl(id_shm, IPC_RMID, 0);
	return 0;
}
