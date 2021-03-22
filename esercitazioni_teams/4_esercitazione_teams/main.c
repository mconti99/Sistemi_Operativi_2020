#include "header.h"

/*Funzione che, per 10 volte,incrementa di uno la posizione molo, ovvero la posizione della nave, e tramite scrivi_molo effettua la modifica poi attende 3 secondi*/
void * gestoreMolo (void * p){
	struct monitor* m = (struct monitor*) p;
	int i,s;
	s=m->molo;
	for(i=0; i<10; i++){
		s=s+1;
		scrivi_molo(m,s);
		printf("[C: Posizione della nave %d modificata. La nuova posizione è: %d]\n",m->id_nave,s);
		sleep(3);
	}
	pthread_exit(NULL);
}

//Funzione che controlla la posizione di un nave per tre volte
void * Viaggiatori (void * p){
	struct monitor* m = (struct monitor*) p;
	int i;
	int ris;
	for(i=0;i<3;i++){
		sleep(rand()%6+1);
		ris=leggi_molo(m);
		printf("[V]~La nave n.ro %d è nel molo %d\n", m->id_nave, ris);
	}
	pthread_exit(NULL);
}

int main() {
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	srand(time(NULL));

	struct monitor* m[5];//l'array di monitor per gestire 5 navi

	pthread_t gestore_molo[5];//5 gestori molo
	pthread_t viagg[10];//10 viaggiatori	
	
	int i;

	for(i=0;i<5;i++){
		m[i]=malloc(sizeof(struct monitor));
		inizializza(m[i]);
	}


	//assegno un id ad ogni nave
	m[0]->id_nave=1;
	m[1]->id_nave=2;
	m[2]->id_nave=3;
	m[3]->id_nave=4;
    	m[4]->id_nave=5;

	for(i=0;i<5;i++){
		printf("sono il thread gestore molo [%d]\n", i);
		pthread_create(&gestore_molo[i], &attr, gestoreMolo, (void*) m[i]);
	}
    
    	for(i=0;i<10;i++){
		printf("sono il thread viaggiatore [%d]\n", i);
		pthread_create(&viagg[i], &attr, Viaggiatori, (void*) m[rand()%5]);
	}

	for(i=0;i<5;i++){
	    	pthread_join(gestore_molo[i], NULL);
		printf("join gestore molo numero [%d]\n", i);

	}	    

	for(i=0;i<10;i++){
		pthread_join(viagg[i], NULL);
		printf("join viaggiatore numero [%d]\n", i);
	}

	pthread_attr_destroy(&attr);
	
	for(i=0;i<5;i++){
		rimuovi(m[i]);
	}

	for(i=0;i<5;i++){
		free(m[i]);
	}
    
	return 0;
}	
