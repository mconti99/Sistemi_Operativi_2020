#include "monitor.h"

struct LettScritt{
	int buffer;
	Monitor m;
	int numero_lettori;
	int numero_scrittori;
}

#define VARCOND_LETTORI 0
#define VARCOND_SCRITTORI 1

void scrivi(struct LettScritt*, int valore);
int leggi(struct LettScritt*);

