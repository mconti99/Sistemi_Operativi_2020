#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include "prodcons.h"
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{

    int shm_id = shmget(IPC_PRIVATE, sizeof(ProdCons), IPC_CREAT|0664);

    if (shm_id < 0)
    {
        perror("Errore creazione shared memory");
        exit(1);
    }

    ProdCons *p = (ProdCons *) shmat(shm_id, NULL, 0);

    if (p == (void *)-1)
    {
        perror("Errore attach shared memory");
        exit(1);
    }

    inizializza(p);

    pid_t pid;
    for(int i=0;i<5;i++){
	    pid=fork();
	    if(pid==0){
		    srand(time(NULL)*getpid());
		    int valore=0;
		    for(int j=0;j<9;j++){
			    valore=rand()%10;
			    produci(p, valore);
			    sleep(2);
		    }
		    exit(0);
	    }else if(pid<0){
		    perror("errore fork");
		    exit(1);
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
	    }else if(pid<0){
		    perror("errore fork");
		    exit(1);
	    }
    }
				

    printf("[%d] Processo padre in attesa...\n", getpid());

    for (int i = 0; i < 10; i++)
    {
        wait(NULL);
    }

    printf("[%d] Terminazione\n", getpid());

    rimuovi(p);

    shmctl(shm_id, IPC_RMID, 0);

    return 0;
}
