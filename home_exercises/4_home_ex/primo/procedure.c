#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

void InizioLettura(Monitor* m, Buffer * buf){
	
	enter_monitor(m);
	buf->numero_lettori++;
	signal_condition(m, VARCOND_LETTORI);
	leave_monitor(m);

}

void FineLettura(Monitor* m, Buffer * buf) {

	enter_monitor(m);
	buf->numero_lettori--;
	if(buf->numero_lettori==0){
		signal_condition(m, VARCOND_SCRITTORI);
	}
	leave_monitor(m);

}



//Procedure di inizio e fine scrittura

void InizioScrittura(Monitor* m,Buffer*buf){

	enter_monitor(m);
	if(buf->numero_lettori>0){
		wait_condition(m, VARCOND_SCRITTORI);
	}
	leave_monitor(m);
}

void FineScrittura(Monitor* m, Buffer*buf){

	enter_monitor(m);
	signal_condition(m, VARCOND_LETTORI);
	leave_monitor(m);
}



void Servizio(Monitor* m, Buffer * buf){

	srand(time(0));

	int i;
	for(i=0; i<20; i++) {

		InizioScrittura(m, buf);

		buf->meteo.temperatura = (rand()%101)-50;
		buf->meteo.umidita = rand()%101;
		buf->meteo.pioggia = rand()%2;
		FineScrittura(m, buf);
		printf("<%d> scrittura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );
		
		sleep(2);
	}

}

void Utente(Monitor* m, Buffer * buf) {

	int i;
	for(i=0; i<10; i++) {
		
		InizioLettura(m, buf);

		printf("<%d> lettura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );
		
		FineLettura(m, buf);
		sleep(1);
	}

}
