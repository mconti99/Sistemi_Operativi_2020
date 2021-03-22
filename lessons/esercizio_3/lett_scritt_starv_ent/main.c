#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include "procedure.h"

int main(){
	int id_sem, id_shared, k;
	key_t chiave =IPC_PRIVATE;
	key_t c_sem=IPC_PRIVATE;
	int status;
	Buffer *ptr_sh;

	pid_t pid;
	int num_processi=10;

	id_shared=shmget(chiave, sizeof(Buffer), IPC_CREAT|0664);
	printf("id_shared=%d\n", id_shared);
	ptr_sh=(Buffer*)shmat(id_shared, 0, 0);

	ptr_sh->numlettori=0;
	ptr_sh->numscrittori=0;
	ptr_sh->messaggio=0;

	id_sem=semget(c_sem, 4, IPC_CREAT|0664);
	semctl(id_sem, SYNCH, SETVAL, 1),
	semctl(id_sem, MUTEXL, SETVAL, 1);
	semctl(id_sem, MUTEXS, SETVAL, 1);
	semctl(id_sem, MUTEX, SETVAL, 1);

	for(k=0;k<num_processi;k++){
		pid=fork();
		if(pid==0){
			if((k%2)==0){
				printf("sono il figlio scrittore. il mio pid %d \n", getpid());
				scrittore(id_sem, ptr_sh);
			}else{
				printf("sono il figlio lettore. Il mio pid %d \n", getpid());
				lettore(id_sem, ptr_sh);
			}
			exit(0);
		}
	}
	for(k=0;k<num_processi;k++){
		pid=wait(&status);
		if(pid==-1) perror("errore");
		else printf("figlio numero %d è morto con status= %d \n", pid, status);

	}
	shmctl(id_shared, IPC_RMID,0);
	semctl(id_sem, 0, IPC_RMID);
	return 0;
}
