#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct{
	int *a;
	int *b;
	int sum;
}dotdata;
pthread_t callThd[4];
pthread_mutex_t mutexsum;

dotdata dotstr;

//dotprod: input ottenuto da una struttura di tipo dotdata, output scritto nella struttura
void *dotprod(void * arg){
	int i, start, end, offset, len;
	int mysum, *x, *y;

	offset=(int)arg;
	//dotstr è condivisa tra i thread, è accessibile in lettura senza bisogno di mutex
	
	start=offset;
	end=start+1;
	x=dotstr.a;
	y=dotstr.b;

	mysum=0;
	for(i=start;i<end;i++){
		mysum +=(x[i]*y[i]);
	}

	//blocco sul mutex prima di aggiornare la variabile condivisa sum e sblocco dopo aver aggiornato
	pthread_mutex_lock(&mutexsum);
	dotstr.sum += mysum;
	pthread_mutex_unlock(&mutexsum);
	pthread_exit((void*)0);
}

//main: inizializza i veottri, crea i thread worker

int main(int argc, char* argv[]){
	int i;
	int *a, *b;
	void * status;
	pthread_attr_t attr;

	//alloca spazio
	a=(int*) malloc(4*sizeof(int));
	b=(int*) malloc(5*sizeof(int));
	for(i=0;i<4;i++){
		a[i]=1;
		b[i]=a[i];
	}
	dotstr.a=a;
	dotstr.b=b;
	dotstr.sum=0;
	//inizializzo il mutex
	pthread_mutex_init(&mutexsum,NULL);


	//creo i thread (joinable)
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int ret=-1;
	for(i=0;i<4;i++){
	printf("creazione thread %d\n", i);
	ret=pthread_create(&callThd[i], &attr, dotprod, (void*)i);
	}

	//aspetta la terminazione dei thread
	int k;
	for(k=0;k<4;k++){
		pthread_join(callThd[k], &status);
	}

	printf("\nProdotto scalare = %d\n", dotstr.sum);
	//rimuove l'attributo usato per definire i thread come joinable
	
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutexsum);
	free(a);
	free(b);

	pthread_exit(0);
		
	return 0;
}
