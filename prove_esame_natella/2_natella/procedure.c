#include "procedure.h"
void generatore(int ds_sem, buffer* p){
	Wait_Sem(ds_sem, MUTEXU);
	p->numt=(p->numt)+1;
	if(p->numt==1) Wait_Sem(ds_sem, SYNCHU);
	Signal_Sem(ds_sem, MUTEXU);
	int termina=0;
	if(p->v==1) termina=1;

	Wait_Sem(ds_sem, MUTEXU);
	p->numt=(p->numt)-1;
	if(p->numt==0) Signal_Sem(ds_sem, SYNCHU);
	Signal_Sem(ds_sem, MUTEXU);

	if(termina==1) return 0;
	sleep(3);
	Wait_Sem(ds_sem, SYNCH);
	for(int i=0;i<p->N;i++){
		for(int j=0;j<p->N;j++){
			p->a[i][j]=rand()%10;
		}
	}
	Signal_Sem(ds_sem, SYNCH);
}

void elaboratore(int ds_sem, buffer* p){
	Wait_Sem(ds_sem, MUTEXU);
        p->numt=(p->numt)+1;
        if(p->numt==1) Wait_Sem(ds_sem, SYNCHU);
        Signal_Sem(ds_sem, MUTEXU);
        int termina=0;
        if(p->v==1) termina=1;

        Wait_Sem(ds_sem, MUTEXU);
        p->numt=(p->numt)-1;
        if(p->numt==0) Signal_Sem(ds_sem, SYNCHU);
        Signal_Sem(ds_sem, MUTEXU);

        if(termina==1) return 0;
        sleep(2);


	Wait_Sem(ds_sem, MUTEXL);
	p->numlettori=p->numlettori + 1;
	if(p->numlettori==1) Wait_Sem(ds_sem, SYNCH);
	Signal_Sem(ds_sem, MUTEXL);

	for(int i=0;i<p->N;i++){
		for(int j=0;j<p->N;j++){
			int z= p->a[i][j]*2;
			printf( "valore: %d  | ", z);
		}
		printf("\n");
	}
	Wait_Sem(ds_sem, MUTEXL);
	p->numlettori=p->numlettori-1;
	if(p->numlettori==0) Signal_Sem(ds_sem, SYNCH);
	Signal_Sem(ds_sem, MUTEXL);
}
void analizzatore(int ds_sem, buffer * p){
	Wait_Sem(ds_sem, MUTEXU);
        p->numt=(p->numt)+1;
        if(p->numt==1) Wait_Sem(ds_sem, SYNCHU);
        Signal_Sem(ds_sem, MUTEXU);
        int termina=0;
        if(p->v==1) termina=1;

        Wait_Sem(ds_sem, MUTEXU);
        p->numt=(p->numt)-1;
        if(p->numt==0) Signal_Sem(ds_sem, SYNCHU);
        Signal_Sem(ds_sem, MUTEXU);

        if(termina==1) return 0;
        sleep(1);


        Wait_Sem(ds_sem, MUTEXL);
        p->numlettori=p->numlettori + 1;
        if(p->numlettori==1) Wait_Sem(ds_sem, SYNCH);
        Signal_Sem(ds_sem, MUTEXL);
	int somma=0;
        for(int i=0;i<p->N;i++){
                for(int j=0;j<p->N;j++){
                         somma+=p->a[i][j];
                }
        }

	float media= somma/(p->N*p->N);
	printf("la media è %f\n", media);
        Wait_Sem(ds_sem, MUTEXL);
        p->numlettori=p->numlettori-1;
        if(p->numlettori==0) Signal_Sem(ds_sem, SYNCH);
        Signal_Sem(ds_sem, MUTEXL);
}
