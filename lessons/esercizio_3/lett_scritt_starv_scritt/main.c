#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "procedure.h"
int main(){
	int sem, id_shared, k, numsem, numlettori, numscrittori;
	key_t chiave=IPC_PRIVATE;
	key_t c_sem=IPC_PRIVATE;

	int status, numprocessi;
	pid_t pid;
	Buffer * buf;

	numlettori=6;
	numscrittori=6;
	int num_processi=numscrittori+ numlettori;

	id_shared=shmget(chiave, sizeof(Buffer), IPC_CREAT|0664);
	printf("id_shared =%d\n", id_shared);
	buf=(Buffer*) shmat(id_shared, 0,0);
	buf->numlettori=0;
	buf->messaggio=0;

	sem=semget(c_sem, 2, IPC_CREAT|0664);
	semctl(sem, MUTEXL, SETVAL,1);
	semctl(sem, SYNCH, SETVAL, 1);

	for(k=0;k<num_processi;k++){
		pid=fork();
		if(pid==0){
			if((k%2)==0){
				printf("sono il figlio scrittore. il mio pid è %d\n", getpid());
				scrittore(sem,buf);
			}else{
				printf("sono il figlio lettore. Il mio pid è %d\n", getpid());
				lettore(sem,buf);
			}
			exit(0);
		}
	}
	for(k=0;k<num_processi;k++){
		pid=wait(&status);
		if(pid==-1)
			perror("errore");
		else 
			printf("figlio numero %d è morto con status=%d\n", pid, status);
	}

	shmctl(id_shared, IPC_RMID,0);
	semctl(sem, 0, IPC_RMID);
	return 0;
}
