#include "header.h"

void produci(int ds_sem, struttura * s, buffer b){
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	Wait_Sem(ds_sem, MUTEXP);
	int i=0;
	while(i<4 && s->stato[i]!=LIBERO){i++;}
	s->stato[i]=INUSO;
	Signal_Sem(ds_sem, MUTEXP);
	sleep(1+rand()%3);
	s->vettore[i]=b;
	s->stato[i]=OCCUPATO;
	Signal_Sem(ds_sem, b.chiave-1);
}

void consuma(int ds_sem, struttura * s, int i, buffer * b){
	Wait_Sem(ds_sem, i);
	int j=0;
	while(j<4 && s->stato[j]!=OCCUPATO && s->vettore[j].chiave==j+1){j++;}
	sleep(1+rand()%3);
	s->stato[j]=INUSO;
	*b=s->vettore[j];
	s->stato[j]=OCCUPATO;
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}
