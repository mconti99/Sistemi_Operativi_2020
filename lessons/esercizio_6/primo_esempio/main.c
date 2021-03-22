#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define NUM_THREADS 5

void *print_hello(void *i){ //i può essere una struttura dati (starting routine)
	printf("HELLO form thread%d\n", i);
	pthread_exit(0); //terminazione thread
}

int main(){

	pthread_t threads[NUM_THREADS];
	int i,rc;
	for(i=0;i<NUM_THREADS;i++){
		printf("creazione thread%d\n", i);
		rc=pthread_create(&threads[i], NULL, print_hello,(void*)i); 
		if(rc){ //se ritorna !=0 c'è qualche problema
			printf("ERROR: return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL); //terminazione main
}
