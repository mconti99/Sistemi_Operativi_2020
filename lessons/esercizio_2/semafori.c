#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "procedure.h"
int main(){
	//allocare e inizializzare i semafori
	key_t k_sem=IPC_PRIVATE;

	int id_sem=semget(k_sem, 1, IPC_CREAT|0664);

	semctl(id_sem, 0, SETVAL, 1);

	printf("sem %d inizializzato a 1\n",id_sem);

	//allocare e inizializzare shared memory
	key_t k_shmem = IPC_PRIVATE;
	int id_shmem = shmget(k_shmem, sizeof(int),IPC_CREAT | 0664);

	if(id_shmem<0){
		perror("Errore  shmget");
		exit(1);
	}

	int *ptr= (int*) shmat(id_shmem, 0,0);
	if(ptr==(void*)-1){
		perror("Error shmat");
		exit(1);
	}

	*ptr=0;
	printf("valore iniziale della shm: %d\n", *ptr);
	//generare i processi figli
	int i;

	for(i=0;i<2;i++){
		pid_t pid = fork();
		
		if(pid<0){
			perror("errore fork");
			exit(1);
		}

		if(pid==0){
			int j;
			for(j=0; j<100;j++){
				Wait_Sem(id_sem,0);
				//INIZIO SEZIONE CRITICA
				printf("sono il figlio: %d\n", getpid());
				int tmp=*ptr;
				printf("processo %d ha letto il valore\n", j);

				*ptr=tmp+1;
				//(*ptr)++;
				//*ptr++; SBAGLIATA perchè prima incrementa l'indirizzo, non il contenuto
				//*(ptr)++; anche questa è sbagliata

				printf("processo %d ha incrementato\n", j);
				//FINE SEZIONE CRITICA
				Signal_Sem(id_sem,0);
				}
			exit(0);
		}	
	}
	//operare sulla sezione critica(aggiornare il valore di 1 sulla shm), wait e signal
	//wait for child termination
	wait(NULL);
	wait(NULL);
	printf("valore shm finale: %d", *ptr);
	//deallocazione shared memory
	shmctl(id_shmem, IPC_RMID, 0);
	//deallocazione semafori
	semctl(id_sem, 0, IPC_RMID);






	return 0;
}
