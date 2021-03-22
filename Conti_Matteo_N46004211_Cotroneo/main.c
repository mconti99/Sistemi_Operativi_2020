#include "prodcons.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void * Produttore(void *);
void * Consumatore(void *);

int main() {

    /* TBD: Avviare i thread produttore e consumatore */
	MonitorStreaming * m=malloc(sizeof(MonitorStreaming));

	inizializza(m);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t threads[2];
	pthread_create(&threads[0], &attr, Produttore, (void*) m);
	pthread_create(&threads[1], &attr, Consumatore, (void*)m);

	for(int i=0;i<2;i++){
		pthread_join(threads[i], NULL);
	}
	pthread_attr_destroy(&attr);
	distruggi(m);
	free(m);
	pthread_exit(NULL);


}

void * Produttore(void * p) {
	MonitorStreaming * m= (MonitorStreaming * ) p;
    for(int i=0; i<10; i++) {

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor */
	produci(m, f);
        sleep(1);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {

    /* TBD: Chiamare il metodo "bufferizza()" del monitor */
	MonitorStreaming * m=(MonitorStreaming * ) p;
	bufferizza(m, 4);

    for(int i=0; i<10; i++) {

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
	consuma(m, f);
        sleep(1);
    }

    pthread_exit(NULL);
}
