#include <stdio.h>
#include <sys/ipc.h>
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

for(int i=0;i<5;i++){
        lettore2(p, n, sem_ds);
}
      
return 0;
}
