#include "header.h"

void inizializzazione(Magazzino * ma){
	for(int i=0;i<10;i++){
		ma[i]->costo=(rand()%5)+1;
		ma[i]->quantita=(rand()%5)+1;
		printf("Prodotto %d con costo %d e quantita %d\n", i, ma[i]->costo, ma[i]->quantita);
	}
}


