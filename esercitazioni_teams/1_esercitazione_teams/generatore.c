#include "header.h"

int main(){
	key_t chiave_shm=ftok(FTOK_PATH, FTOK_CHAR);

        int ds_shm=shmget(chiave_shm, sizeof(buffer), IPC_CREAT|0664);
        if(ds_shm<0){perror("errore shmget"); exit(1);}

        buffer * p;

        p=(buffer *) shmat(ds_shm, NULL, 0);

        if(p==(void*)-1) {perror("errore shmat"); exit(1);}

        key_t chiave_sem=ftok(FTOK_PATH, FTOK_CHAR1);

        int sem=semget(chiave_sem, 2, IPC_CREAT|0664);
	srand(time(NULL));
	while(1){
		sleep(3);
		Wait_Sem(sem, SYNCH);
		for(int i=0;i<p->N;i++){
			p->str[i]='a' + (rand() % 26);
		}
		p->str[(p->N)]=0;
		printf("stringa generata: %s\n", p->str);
		sleep(1);
		Signal_Sem(sem, SYNCH);
	}
	return 0;
}

