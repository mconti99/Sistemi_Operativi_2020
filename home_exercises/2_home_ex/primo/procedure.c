#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void produttore(posto * p, int *d, int ds_sem) {
    int indice = 0;
    sleep(rand()%6);
    
    int i=rand()%4; //posti da prenotare
    Wait_Sem(ds_sem, MUTEX_VAR);
    if(*d<i+1){
	    printf("disponibilità esaurita\n");
	    Signal_Sem(ds_sem, MUTEX_VAR);
	    //exit?
	    exit(0);
    }
    else{
	Wait_Sem(ds_sem, MUTEX_VETT);
   	for(indice=0; indice<DIM_BUFFER;indice++){
   		while(indice <= DIM_BUFFER && p[indice].stato != BUFFER_VUOTO) indice++;
    		switch(i){
			case 1:
			p[indice].stato= BUFFER_INUSO;
			*d=*d-1;
			Signal_Sem(ds_sem, MUTEX_VAR);
			Signal_Sem(ds_sem, MUTEX_VETT);
			sleep(1);
			p[indice].stato=BUFFER_PIENO;
			p[indice].id_cliente=getpid();
			break;
			case 2:
			p[indice].stato= BUFFER_INUSO;
			p[indice+1].stato=BUFFER_INUSO;
			*d=*d-2;
			Signal_Sem(ds_sem, MUTEX_VAR);
			Signal_Sem(ds_sem, MUTEX_VETT);
			sleep(1);
			p[indice].stato=BUFFER_PIENO;
			p[indice+1].stato=BUFFER_PIENO;
			p[indice].id_cliente=getpid();
			p[indice+1].id_cliente=getpid();
			break;
			case 3:
			p[indice].stato=BUFFER_INUSO;
			p[indice+1].stato=BUFFER_INUSO;
			p[indice+2].stato=BUFFER_INUSO;
			*d=*d-3;
			Signal_Sem(ds_sem, MUTEX_VAR);
			Signal_Sem(ds_sem, MUTEX_VETT);
			sleep(1);
			p[indice].stato=BUFFER_PIENO;
                        p[indice+1].stato=BUFFER_PIENO;
			p[indice+2].stato=BUFFER_PIENO;
                        p[indice].id_cliente=getpid();
                        p[indice+1].id_cliente=getpid();
			p[indice+2].id_cliente=getpid();
			break;
			case 4:
			p[indice].stato=BUFFER_INUSO;
                        p[indice+1].stato=BUFFER_INUSO;
                        p[indice+2].stato=BUFFER_INUSO;
			p[indice+3].stato=BUFFER_INUSO;
                        *d=*d-4;
                        Signal_Sem(ds_sem, MUTEX_VAR);
                        Signal_Sem(ds_sem, MUTEX_VETT);
                        sleep(1);
                        p[indice].stato=BUFFER_PIENO;
                        p[indice+1].stato=BUFFER_PIENO;
                        p[indice+2].stato=BUFFER_PIENO;
			p[indice+3].stato=BUFFER_PIENO;
                        p[indice].id_cliente=getpid();
                        p[indice+1].id_cliente=getpid();
                        p[indice+2].id_cliente=getpid();
			p[indice+3].id_cliente=getpid();
			break;
		}
/*
		p[indice].stato  = BUFFER_INUSO;
    		*d=*d-1;
    		sleep(1);
    		p[indice].stato = BUFFER_PIENO;
    		p[indice].id_cliente = getpid();
   		}
        Signal_Sem(ds_sem, MUTEX_VAR);
        Signal_Sem(ds_sem, MUTEX_VETT);*/
	}
}
}

