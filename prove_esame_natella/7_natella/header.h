#ifndef _HEADER_H
#define _HEADER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "monitor.h"
#define LETTORI 0
#define SCRITTORI 1

struct MonitorLettScritt {
	int variabile;  // variabile condivisa (tra 0 e 99)
    	int versione;   // variabile che indica il numero di scritture effettuate
	int numero_lettori;
	int numero_scrittori;
	Monitor m;
};

void leggi(struct MonitorLettScritt * m, int *);
void scrivi(struct MonitorLettScritt * m, int nuovovalore);

#endif
