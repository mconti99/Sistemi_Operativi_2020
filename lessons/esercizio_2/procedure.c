#include "procedure.h"
#include <stdio.h>
#include <errno.h>
int Wait_Sem(int id_sem,int numsem){
	struct sembuf sem_buf;
	int err;

	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op = -1;
	
	err = semop(id_sem, &sem_buf, 1);
	if(err<0){
		perror("Errore nella wait\n");
	}
	return err;
}

int Signal_Sem(int id_sem,int numsem){
        struct sembuf sem_buf;
        int err;

        sem_buf.sem_num=numsem;
        sem_buf.sem_flg=0;
        sem_buf.sem_op = 1;

        err = semop(id_sem, &sem_buf, 1);
        if(err<0){
                perror("Errore nella signal\n");
        }
        return err;
}
