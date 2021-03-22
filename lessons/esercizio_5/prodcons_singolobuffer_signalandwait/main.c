#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "procedure.h"

#define NUM_PRODUTTORI 1
#define NUM_CONSUMATORI 1

int main(){
	key_t chiave_shm =IPC_PRIVATE;

	int id_shm=shmget(chiave_shm, sizeof(struct ProdCons), IPC_CREAT|0664);

	//check id_shm<0
	struct ProdCons *pc=(struct ProdCons*) shmat(id_shm, NULL, 0);

	//check *pc != (void*)-1
	
	init_monitor(&(pc->m), 2);
	pc->buffer_libero=1;
	pc->buffer_occupato=0;
	
	pid_t pid;
	for(int i=0;i<NUM_CONSUMATORI;i++){
		pid=fork();
		if(pid==0){
			printf("Avvio consumatore\n");
			Consuma(pc);
			printf("consumatore consuma");
			exit(0);
		}
	}

	  for(int i=0;i<NUM_PRODUTTORI;i++){
                pid=fork();
                if(pid==0){
                        printf("Avvio prod\n");
			int valore=rand()%10;
			Produci(pc, valore);
                        printf("prod produce: %d\n", valore);
                        exit(0);
                }
        }

	  for( int i=0;i<NUM_CONSUMATORI+ NUM_PRODUTTORI;i++) wait(NULL);

	  remove_monitor(&(pc->m));

	  shmctl(id_shm, IPC_RMID, 0);
	  return 0;
}
