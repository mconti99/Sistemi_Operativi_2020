#include <stdio.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "procedure.h"
#include "semafori.h"

int main(){
	key_t shm_chiave=ftok(FTOK_PATH, FTOK_CHAR);

	int shm_ds=shmget(shm_chiave, sizeof(buffer), IPC_CREAT|0664);

	if(shm_ds<0){perror("shm get");exit(1);}

	buffer * p;

	p=(buffer *)shmat(shm_ds, NULL,0);
	if(p==(void*)-1){perror("errore shmat");exit(1);}

	key_t chiave_1=ftok(FTOK_PATH, 'c');
        int shm_1=shmget(chiave_1, sizeof(int), IPC_CREAT|0664);

	if(shm_1<0){perror("shm get"); exit(1);}

	int * n;

	n=(int *)shmat(shm_ds,NULL,0);

	key_t sem_chiave=ftok(FTOK_PATH, 'b');
	int sem_ds=semget(sem_chiave, 2,IPC_CREAT|0664);
	
	semctl(sem_ds, 0, SETVAL, 1);
	semctl(sem_ds, 1, SETVAL, 1);	

	pid_t pid=fork();
	if(pid==0){
		execl("./scrittore", "./scrittore", (char*)0);
		perror("exec fallita");
		exit(1);
	}else if(pid<0){
		perror("fork fallita");
		exit(1);
	}

	pid = fork();

	if(pid==0) {

		execl("./lettore", "./lettore", (char*) 0);

		perror("Exec fallita");
		exit(1);

	} else if(pid<0) {

		perror("Fork fallita");
		exit(1);
	}

	        pid = fork();

        if(pid==0) {

                execl("./lettore1", "./lettore1", (char*) 0);

                perror("Exec fallita");
                exit(1);

        } else if(pid<0) {

                perror("Fork fallita");
                exit(1);
        }


	for(int i=0; i<3; i++) {
		wait(NULL);
	}



        shmctl(shm_1, IPC_RMID, 0);
	shmctl(shm_ds, IPC_RMID, 0);
	semctl(sem_ds, 0, IPC_RMID);

	return 0;
}
