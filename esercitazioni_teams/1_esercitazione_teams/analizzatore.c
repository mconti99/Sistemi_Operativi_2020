#include "header.h"

int main(){
	key_t chiave_shm=ftok(FTOK_PATH, FTOK_CHAR);

        int ds_shm=shmget(chiave_shm, sizeof(buffer), IPC_CREAT|0664);
        if(ds_shm<0){perror("errore shmget"); exit(1);}

        buffer * p;

        p=(buffer *) shmat(ds_shm, NULL,0);

        if(p==(void*)-1) {perror("errore shmat"); exit(1);}

        key_t chiave_sem=ftok(FTOK_PATH, FTOK_CHAR1);
	char supporto[16];
	supporto[0]=0;
        int sem=semget(chiave_sem, 2, IPC_CREAT|0664);
	while(1){
		sleep(2);
		Wait_Sem(sem, MUTEXL);
		p->numlettori=p->numlettori+1;
		if(p->numlettori==1) Wait_Sem(sem, SYNCH);
		Signal_Sem(sem, MUTEXL);
		for(int i=0;i<strlen(p->str);i++){
			supporto[i]=p->str[p->N-i-1];
		}
		supporto[p->N]='\0';
		printf("stringa invertita: %s \n", supporto);
		Wait_Sem(sem, MUTEXL);
		p->numlettori=p->numlettori-1;
		if(p->numlettori==0) Signal_Sem(sem, SYNCH);
		Signal_Sem(sem, MUTEXL);
	}
	return 0;
}
