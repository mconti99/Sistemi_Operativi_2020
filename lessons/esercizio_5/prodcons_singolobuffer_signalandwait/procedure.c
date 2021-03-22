#include "procedure.h"
#include <stdio.h>

void Produci(struct ProdCons * pc, int valore){
	//entro nel monitor
	enter_monitor(&(pc->m));
	printf("entro nel monitor\n");
	//aspetto che ci sia spazio disponibile
	if(pc->buffer_occupato==1){
	printf("attesa prod condition\n");
	wait_condition(&(pc->m), VARCOND_PRODUTTORI);
	printf("riattivazione prod\n");
	}

	//produzione
	pc->buffer=valore;
	pc->buffer_occupato=1;
	pc->buffer_libero=0;

	printf("produzione del valore %d", pc->buffer);
	signal_condition(&(pc->m), VARCOND_CONSUMATORI); //segnalo al consumatore
	leave_monitor(&(pc->m));
}

void Consuma(struct ProdCons * pc){
	enter_monitor(&(pc->m));

	//aspetto che ci sia un valore all'interno del buffer
	if(pc->buffer_libero==1){
		printf("attesa cons condition\n");
		wait_condition(&(pc->m), VARCOND_CONSUMATORI);
		printf("riattivazione cons");
	}

	//consumo
	int valore;
	valore=pc->buffer;
	printf("consumo valore %d\n", valore);
	
 	pc->buffer_occupato=0;
	pc->buffer_libero=1;

	signal_condition (&(pc->m), VARCOND_PRODUTTORI);

	leave_monitor(&(pc->m));

}
