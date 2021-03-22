#include "monitor_hoare.h"

#define NUM_UTENTI 10
#define NUM_CONDITIONS 2

#define LETTORI 0
#define SCRITTORI 1

typedef struct {
	int temperatura;
	unsigned int umidita;
	unsigned short pioggia;
} meteo;

typedef struct {
	meteo meteo;
	
	int num_lettori;
	int num_scrittori;
	
} Buffer;


void Servizio(Monitor* m, Buffer * buf);
void Utente(Monitor* m, Buffer * buf);
