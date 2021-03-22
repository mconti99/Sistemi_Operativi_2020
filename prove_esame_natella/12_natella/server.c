#include "header.h"

int main(){
	init();
        key_t key=ftok(".",'c');
        coda=msgget(key, IPC_CREAT|0664);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t threads[2];
	for(int i=0;i<2;i++){
		//printf("MAIN SERVER: Creo il pthread %d\n", i);
		pthread_create(&threads[i], &attr, receiver, (void*) NULL);
	}
	for(int i=0;i<2;i++){
		pthread_join(threads[i], NULL);
	}
	pthread_attr_destroy(&attr);
	pthread_exit(0);
}
