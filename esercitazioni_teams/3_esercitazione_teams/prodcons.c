#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"

void inizializza(ProdCons * p) {
	
	init_monitor(&(p->m), 2);
	p->totale_elementi=0;
	p->testa=0;
	p->coda=0;
	for(int i=0;i<10;i++){
		p->vettore[i]=0;
	}
}

void consuma(ProdCons * p) {

    enter_monitor(&(p->m));


    printf("[%d] Ingresso consumatore\n", getpid());

    if(p->totale_elementi<3){
	    wait_condition(&(p->m), VARCOND_CONSUMATORI);
    }

    long valore1, valore2, valore3;
    valore1=p->vettore[p->coda];

    p->coda=(p->coda+1)%DIM;

    valore2=p->vettore[p->coda];

    p->coda=(p->coda+1)%DIM;

    valore3=p->vettore[p->coda];

    p->coda=(p->coda+1)%DIM;
    
    p->totale_elementi=p->totale_elementi -3;
    printf("ho consumato i valori ---> [%ld] [%ld] [%ld]\n", valore1, valore2, valore3);

	
    for(int i=0;i<3;i++){
    signal_condition(&(p->m), VARCOND_PRODUTTORI);
    }


    printf("[%d] Uscita consumatore\n", getpid());

    leave_monitor(&(p->m));
}

void produci(ProdCons * p, int val) {

    enter_monitor(&(p->m));

    printf("[%d] Ingresso produttore\n", getpid());

    if(p->totale_elementi==DIM){
	    wait_condition(&(p->m), VARCOND_PRODUTTORI);
    }


    p->vettore[p->testa] = val;
    p->testa = (p->testa + 1) % DIM;
    p->totale_elementi++;

    printf("[%d] Produzione: val=%d\n", getpid(), val);

    
    if(p->totale_elementi>2){
	    signal_condition(&(p->m), VARCOND_CONSUMATORI);
    }

    printf("[%d] Uscita produttore\n", getpid());

    leave_monitor(&(p->m));
}

void rimuovi(ProdCons * p) {

	remove_monitor(&(p->m));
}
