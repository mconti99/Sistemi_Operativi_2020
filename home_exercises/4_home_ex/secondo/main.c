#include "monitor.h"
#include "procedure.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PRODUTTORI_1  1
#define NUM_PRODUTTORI_2  3
#define NUM_CONSUMATORI  1

#define NUM_PRODUZIONI_1  3
#define NUM_PRODUZIONI_2  3
#define NUM_CONSUMAZIONI  12

int main(int argc,char* argv[])
{
	
	int status,indice;
	PriorityProdCons* p = NULL;
	int id_prod_cons;
	pid_t pid;

    
    //richiesta del buffer

	id_prod_cons=shmget(IPC_PRIVATE, sizeof(PriorityProdCons), IPC_CREAT|0664);

	printf("[DEBUG] - id_monitor=%d \n",id_prod_cons);
    
	p = shmat(id_prod_cons, 0, 0);
	
    inizializza_prod_cons(p);

    
	srand(time(NULL));

	
    
	// generazione produttori e consumatori
	int i,k;
	for (k=0;k<NUM_PRODUTTORI_1;k++) {
		pid=fork();
		if (pid==0)  {                //processo figlio
			printf("sono il produttore HIGH PRIORITY. Il mio pid %d \n",getpid());
			i = 0;
			while(i < NUM_PRODUZIONI_1){
			
				produci_alta_prio(p);
				sleep(1);
				i++;
			}
			_exit(0);
		}
	}

	for (k=0;k<NUM_PRODUTTORI_2;k++) {
		pid=fork();
		if (pid==0)  {  
	        //processo figlio
			i = 0;
			printf("sono il produttore LOW PRIORITY. Il mio pid %d \n",getpid());

			while(i < NUM_PRODUZIONI_2){
				
				produci_bassa_prio(p);
				sleep(1);
				i++;
			}
			_exit(0);
		}
	}

	for (k=0;k<NUM_CONSUMATORI;k++) {

		pid=fork();
		if (pid==0)  {                //processo figlio
			printf("sono il consumatore. Il mio pid %d \n",getpid());
			i = 0;
			while(i < NUM_CONSUMAZIONI){
				sleep(2);

				consuma(p);
				i++;
			}
			_exit(0);
		}
	}


	int num_processi = NUM_PRODUTTORI_1 + NUM_PRODUTTORI_2 + NUM_CONSUMATORI;

	for (k=0; k<num_processi;k++) {

		pid=wait(&status);
		if (pid==-1) {
			 perror("errore");
		} else {
			 printf ("Figlio n.ro %d è morto con status= %d \n ",pid,status);
		}
	}

	printf("Processo padre terminato...\n");

	// rimozione memoria condivisa e semafori
	rimuovi_prod_cons(p);
	shmctl(id_prod_cons,IPC_RMID,0);

	return 0;
}
