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
	semctl(sem, 0, SETVAL, 1);
	semctl(sem, 1, SETVAL, 1);

	srand(time(NULL));
	p->N=rand()%6 + 10;

	p->str[0]='\0'; //inizializzo la stringa
	
	p->numlettori=0;

	pid_t pid;
	pid=fork();
	if(pid==0){
		execl("./generatore","generatore", (char*)0);
		printf("exec fallita\n");
		exit(1);
	}else if(pid<0){
		perror("fork fallita");
		exit(1);
	}

        pid=fork();
        if(pid==0){
               execl("./elaboratore","elaboratore", (char*)0);
		printf("exec fallita\n");
		exit(1);
        }else if(pid<0){
                perror("fork fallita");
		exit(1);
        }  
	for(int i=0;i<2;i++){

       		pid=fork();
        	if(pid==0){
              	execl("./analizzatore","analizzatore", (char*)0);
			printf("exec fallita\n");
			exit(1);
		}else if(pid<0){
                	perror("fork fallita");
			exit(1);
        	}
	}

	for(int i=0;i<4;i++){
		wait(NULL);
	}
	semctl(sem, 0, IPC_RMID);
	shmctl(ds_shm, IPC_RMID, 0);
	return 0;
}
