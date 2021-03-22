#include "header.h"
#include "semafori.h"
#include "string.h"
void docente(int ds_sem, struttura* s){
	for(int i=0;i<3;i++){
	Wait_Sem(ds_sem, MUTEXS);
	if(i==0)strcpy(s->appello, "11/09/2011");
	else if(i==1) strcpy(s->appello, "01/07/1999");
	else strcpy(s->appello, "porcoziooo");
	Signal_Sem(ds_sem, MUTEXS);
	sleep(3);
	Wait_Sem(ds_sem, MUTEXN);
	printf("DOCENTE: numero prenotati %d\n", s->numero_prenotati);
	s->numero_prenotati=0;
	Signal_Sem(ds_sem, MUTEXN);
	}
}

void studente(int ds_sem, struttura * s ){
	srand(time(NULL)*getpid());
	sleep(rand()%9);
	Wait_Sem(ds_sem, MUTEXL);
	s->numero_lettori++;
	if(s->numero_lettori==1) Wait_Sem(ds_sem, MUTEXS);
	Signal_Sem(ds_sem, MUTEXL);

	printf("STUDENTE: data appello: %s\n", s->appello);
	Wait_Sem(ds_sem, MUTEXN);
        s->numero_prenotati++;
        Signal_Sem(ds_sem, MUTEXN);

	Wait_Sem(ds_sem, MUTEXL);
	s->numero_lettori--;
	if(s->numero_lettori==0) Signal_Sem(ds_sem, MUTEXS);
	Signal_Sem(ds_sem, MUTEXL);
}


