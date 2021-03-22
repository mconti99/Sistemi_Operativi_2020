/*IMPLEMENTAZIONE DELLE PROCEDURE*/

#include "procedure.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define VARCOND_CONSUMATORI 0
#define VARCOND_PRODUTTORIPLUS 1
#define VARCOND_PRODUTTORI 2


void inizializza_prod_cons(PriorityProdCons* p){

	p->testa=0;
	p->coda=0;
	p->contatore=0;
	for(int i=0;i<3;i++)
		p->buffer[i]=0;

	init_monitor(&(p->m), 3);

}

void rimuovi_prod_cons(PriorityProdCons* p){

	remove_monitor(&(p->m));
}


void produci_alta_prio(PriorityProdCons* p){

	int value;

	enter_monitor(&(p->m));

	//Aumenta il numero di produttori
	printf("Produttore HIGH PRIORITY entrato nel monitor...\n");

	while(p->contatore==3){
		wait_condition(&(p->m), VARCOND_PRODUTTORIPLUS);
	}	
	//Produco il valore
	value = rand() % 12 ;

	//Modifico il buffer
	p->buffer[p->testa] = value;
	p->testa = (p->testa + 1) % DIM;
	p->contatore++;

	//Il buffer non è vuoto
	printf("Produttore HIGH PRIORITY con pid %d ha prodotto %d\n",getpid(),value);	
	
	signal_condition(&(p->m), VARCOND_CONSUMATORI);
	
	leave_monitor(&(p->m));
}

void produci_bassa_prio(PriorityProdCons* p){

	int value;
	
	enter_monitor(&(p->m));
	
	//Aumenta il numero di produttori
	printf("Produttore LOW PRIORITY entrato nel monitor...\n");
	
	while(p->contatore==3){
		wait_condition(&(p->m), VARCOND_PRODUTTORI);
	}

	//Produco il valore
	value = 13 + (rand() % 12) ;

	//Modifico il buffer
	p->buffer[p->testa] = value;
	p->testa = (p->testa + 1) % DIM;
	p->contatore++;

	//Il buffer non è vuoto
	printf("Produttore LOW PRIORITY con pid %d ha prodotto %d\n",getpid(),value);	

	signal_condition(&(p->m), VARCOND_CONSUMATORI);

	leave_monitor(&(p->m));

}

void consuma(PriorityProdCons* p){

	int value;

	enter_monitor(&(p->m));

	/* TBD: Sospendere qui il processo se il vettore di buffer è vuoto */
	while(p->contatore==0){
		wait_condition(&(p->m), VARCOND_CONSUMATORI);
	}


	value = p->buffer[p->coda];
	p->coda = (p->coda + 1) % DIM; //incremento la coda
	p->contatore--;

	printf("Consumatore con pid %d ha consumato valore %d\n",getpid(),value);

	if(queue_condition(&(p->m),VARCOND_PRODUTTORIPLUS)>0){
		signal_condition(&(p->m),VARCOND_PRODUTTORIPLUS);
	}else{
		signal_condition(&(p->m), VARCOND_PRODUTTORI);
	}


	leave_monitor(&(p->m));
}
