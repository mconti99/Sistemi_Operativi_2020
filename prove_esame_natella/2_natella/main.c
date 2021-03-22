#include "procedure.h"

int main(){
	key_t chiave=ftok(FTOK_PATH, FTOK_CHAR);
	
	int ds_shm =shmget(chiave, sizeof(buffer), IPC_CREAT|0664);

        buffer *p;
        p=shmat(ds_shm, NULL, 0);
	
	p->v=0;
	p->numt=0;
	p->numlettori=0;
	srand(time(NULL));
	(p->N)=(rand()%3) +3;

        key_t chiave1=ftok(FTOK_PATH, FTOK_CHAR1);
        int ds_sem=semget(chiave1, 4, IPC_CREAT|0664);

        semctl(ds_sem, SYNCHU, SETVAL, 1);
        semctl(ds_sem, MUTEXL, SETVAL, 1);
        semctl(ds_sem, SYNCH, SETVAL, 1);
	semctl(ds_sem, MUTEXU, SETVAL, 1);

        pid_t pid=fork();
        if(pid==0){
                execl("./generatore","generatore", (char*)0);
                sleep((rand()%3)+1);
        }
        for(int i=0;i<2;i++){
        pid_t pid=fork();
        if(pid==0){
                execl("./analizzatore", "analizzatore", (char*)0);
                sleep((rand()%3)+1);
        }
	if(pid==0){
		execl("./elaboratore","elaboratore", (char*)0);
	}

	sleep(15);
	Wait_Sem(ds_sem,MUTEXU);
	p->v=1;
	Signal_Sem(ds_sem, MUTEXU);
        for(int i=0;i<4;i++){
                wait(NULL);
        }


        shmctl(ds_shm, IPC_RMID, 0);
        semctl(ds_sem, 0,IPC_RMID);

	return 0;
}}
