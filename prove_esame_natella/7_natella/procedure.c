#include "header.h"

void leggi(struct MonitorLettScritt * p, int* x){
	int valore;
	printf("PROBLEMA: CIAO\n");
	enter_monitor(&(p->m));
	while(p->numero_scrittori >0 || p->versione<=(*x)){
		printf("PROBLEMA: lettore si mette in attesa\n");
		wait_condition(&(p->m), LETTORI);
	}
	p->numero_lettori++;
	leave_monitor(&(p->m));
	valore=p->variabile;
	*x=p->versione;
	printf("LETTORI: valore: %d e sua attuale versione: %d\n", valore, *x);
	enter_monitor(&(p->m));
	p->numero_lettori--;
	if(p->numero_lettori==0){
		signal_condition(&(p->m), SCRITTORI);
	}
	leave_monitor(&(p->m));
}
void scrivi(struct MonitorLettScritt * p, int nuovovalore){
	enter_monitor(&(p->m));
	while(p->numero_lettori>0 || p->numero_scrittori>0){
		wait_condition(&(p->m), SCRITTORI);
	}
	p->numero_scrittori++;
	leave_monitor(&(p->m));
	p->variabile=nuovovalore;
	p->versione++;
	printf("SCRITTORI: valore: %d e sua attuale versione: %d\n", p->variabile, p->versione);
	enter_monitor(&(p->m));
	p->numero_scrittori--;
	if(queue_condition(&(p->m), SCRITTORI)>0){
		signal_condition(&(p->m), SCRITTORI);
	}else{
		printf("%d\n", queue_condition(&(p->m), LETTORI));
		while(queue_condition(&(p->m), LETTORI)>0) signal_condition(&(p->m), LETTORI);
	}
	leave_monitor(&(p->m));
}
