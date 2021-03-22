#include "procedure.h"

#include <unistd.h>
#include <stdio.h>

void Produci(struct ProdCons *pc, int valore){
	enter_monitor(&(pc->m));
	while(pc->numero_liberi==0){
		printf("sospensione\n");
		wait_condition(&(pc->m), VARCOND_PRODUTTORI);
		printf("riattivazione\n");
	}

	int i=0;
	while(i<DIM && pc->stato[i]!=LIBERO){i++;}

	pc->stato[i]=IN_USO;
	pc->numero_liberi--;
	leave_monitor(&(pc->m));

	sleep(2);
	pc->buffer[i]=valore;

	enter_monitor(&(pc->m));
	pc->stato[i]=OCCUPATO;
	pc->numero_occupati++; //variabile condivisa

	signal_condition(&(pc->m), VARCOND_CONSUMATORI);
	leave_monitor(&(pc->m));
}

int Consuma(struct ProdCons *pc){
	int valore;
	enter_monitor(&(pc->m));

	while(pc->numero_occupati==0){
		printf("sospensione\n");
		wait_condition(&(pc->m), VARCOND_CONSUMATORI);
		printf("riattivazione\n");
	}
	int i=0;
	while(i<DIM && pc->stato[i]!=OCCUPATO){i++;}

	pc->stato[i]=IN_USO;
	pc->numero_occupati--;

	leave_monitor(&(pc->m));

	sleep(2);
	valore=pc->buffer[i];

	enter_monitor(&(pc->m));
	pc->stato[i]=LIBERO;
	pc->numero_liberi++;

	signal_condition(&(pc->m), VARCOND_PRODUTTORI);
	leave_monitor(&(pc->m));
	return valore;
}
