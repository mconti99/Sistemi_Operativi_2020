#include "header.h"

void produci(prodcons* p, int valore){
	enter_monitor(&(p->m));
	if(p->contatore==N){
		wait_condition(&(p->m), PRODUTTORI);
	}
	p->buffer[p->testa]=valore;
	p->testa=(p->testa+1)%N;
	p->contatore++;
	printf("ciao, ho prodotto %d\n", valore);
	if(p->contatore>1) signal_condition(&(p->m), CONSUMATORI); //i consumatori possono produrre solo quando ci sono già 2 elementi disponibili
	leave_monitor(&(p->m));
}
void consuma(prodcons* p){
	int valore;
	int valore1;
	enter_monitor(&(p->m));
	if(p->contatore<2){
		wait_condition(&(p->m), CONSUMATORI);
	}
	valore=p->buffer[p->coda];
	valore1=p->buffer[p->coda+1];
	p->coda=(p->coda+2)%N;
	p->contatore--;
	p->contatore--;
	printf("hello, i consumed %d and %d\n", valore, valore1);
	signal_condition(&(p->m), PRODUTTORI);
	signal_condition(&(p->m), PRODUTTORI);
	leave_monitor(&(p->m));
}

