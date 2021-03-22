#include "procedure.h"

void produci(coda * c){
	enter_monitor(&(c->m));
	if(c->contatore==10){
		wait_condition(&(c->m), VARCOND_PRODUTTORI);
	}
	
	unsigned int i=rand()%20;
	int j=getpid();
	c->r[c->coda].processo=j;
	c->r[c->coda].posizione=i;
	c->contatore++;
	printf("PRODUTTORE: valore: %d, posizione: %d, contatore: %d\n", c->r[c->coda].processo, c->r[c->coda].posizione, c->contatore);
	c->coda=(c->coda+1) % 10; 
	signal_condition(&(c->m), VARCOND_CONSUMATORI);

	leave_monitor(&(c->m));

}

void consuma(coda * c, richiesta * r){
	enter_monitor(&(c->m));
	if(c->contatore==0){
		wait_condition(&(c->m), VARCOND_CONSUMATORI);
	}
	
	r->processo=c->r[c->testa].processo;
	r->posizione=c->r[c->testa].posizione;
	c->contatore--;
	printf("CONSUMATORE: valore: %d, posizione: %d, contatore: %d\n", r->processo, r->posizione, c->contatore);

	c->testa=(c->testa+1)%10;
	signal_condition(&(c->m), VARCOND_PRODUTTORI);
	leave_monitor(&(c->m));

}
