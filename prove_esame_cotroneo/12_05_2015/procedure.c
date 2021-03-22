#include "procedure.h"

void inseriscivolo(gestionevoli *g, int identificativo){
	enter_monitor(&(g->m));
	while(g->numero_liberi==0){
		wait_condition(&(g->m), VARCOND_PRODUTTORI);
	}
       	int i=0;
	while(i<3 && g->vettore_stato[i]!=LIBERO){i++;}
	g->vettore_stato[i]=IN_USO;
	g->numero_liberi--;
	leave_monitor(&(g->m));

	g->vettore_voli[i].identificativo=identificativo;
	g->vettore_voli[i].quota=0;
	sleep(1);
	enter_monitor(&(g->m));
	g->vettore_stato[i]=OCCUPATO;
	g->numero_occupati++;
	leave_monitor(&(g->m));
}

void rimuovivolo(gestionevoli *g, int identificativo){
	enter_monitor(&(g->m));
	/*while(g->numero_occupati==0){
		wait_condition(&(g->m), VARCOND_CONS);
	}*/
	int i=0;
	while(i<3 && g->vettore_stato[i]!=OCCUPATO && identificativo==g->vettore_voli[i].identificativo){i++;}
	g->vettore_stato[i]=IN_USO;
	g->numero_occupati--;
	leave_monitor(&(g->m));
	
	sleep(1);
	enter_monitor(&(g->m));
	g->vettore_stato[i]=LIBERO;
	g->numero_liberi++;
	signal_condition(&(g->m), VARCOND_PRODUTTORI);
	leave_monitor(&(g->m));
				
}

void aggiornavolo(gestionevoli *g, int identificativo, int quota){
        enter_monitor(&(g->m));
	int i=0;
        while(i<3 && g->vettore_stato[i]!=OCCUPATO && identificativo==g->vettore_voli[i].identificativo){i++;}
        g->vettore_stato[i]=IN_USO;
        leave_monitor(&(g->m));
	g->vettore_voli[i].quota=quota;
	int j= 1+rand()%3;
        sleep(j);
        enter_monitor(&(g->m));
        g->vettore_stato[i]=OCCUPATO;
        signal_condition(&(g->m), VARCOND_PRODUTTORI);
        leave_monitor(&(g->m));

}

void funzione(gestionevoli *v, int i){
	int identificativo=i;
inseriscivolo(v, identificativo);
aggiornavolo(v, identificativo, 1000);
aggiornavolo(v, identificativo, 2000);
aggiornavolo(v, identificativo, 1000);
rimuovivolo(v, identificativo);
}
