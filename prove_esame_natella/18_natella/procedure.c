#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

void InizioLettura(Monitor* m, Buffer * buf){
	
	/* TBD: Effettuare inizio lettura */
	enter_monitor(m);
	if(buf->num_scrittori>0){
		wait_condition(m, LETTORI);
	}
	buf->num_lettori++;
	signal_condition(m, LETTORI);
	leave_monitor(m);


}

void FineLettura(Monitor* m, Buffer * buf) {

	enter_monitor(m);
	buf->num_lettori--;
	if(buf->num_lettori==0){
		signal_condition(m, SCRITTORI);
	}
	leave_monitor(m);

}



//Procedure di inizio e fine scrittura

void InizioScrittura(Monitor* m,Buffer*buf){

	enter_monitor(m);
	if(buf->num_lettori > 0 || buf->num_scrittori>0){
		wait_condition(m, SCRITTORI);
	}
	buf->num_scrittori++;
	leave_monitor(m);

}

void FineScrittura(Monitor* m, Buffer*buf){

	/* TBD: Effettuare inizio scrittura */
	enter_monitor(m);
	buf->num_scrittori--;
	signal_condition(m, LETTORI);
	leave_monitor(m);
}



void Servizio(Monitor* m, Buffer * buf){

	srand(time(0));

	int i;
	for(i=0; i<20; i++) {

		/* TBD: Richiamare InizioScrittura e FineScrittura */
		InizioScrittura(m, buf);
		buf->meteo.temperatura = (rand()%101)-50;
		buf->meteo.umidita = rand()%101;
		buf->meteo.pioggia = rand()%2;

		printf("<%d> scrittura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		FineScrittura(m, buf);
	}

}

void Utente(Monitor* m, Buffer * buf) {

	int i;
	for(i=0; i<10; i++) {
		
		/* TBD: Richiamare InizioLettura e FineLettura */
		InizioLettura(m, buf);
		printf("<%d> lettura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );
		FineLettura(m, buf);
	}

}
