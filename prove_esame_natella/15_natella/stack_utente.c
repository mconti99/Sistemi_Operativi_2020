#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *Inserisci(void * s)
{

	int i;
	Elem v;
	Stack * p = (Stack * ) s;

	for(i=0; i<4; i++) {

		v = rand() % 11;
		
		StackPush(p, v);
		/* TBD: Effettuare un inserimento con StackPush() */ 
		
		sleep(1);
	}

	pthread_exit(NULL);
}


void *Preleva(void * s)
{

	int i;
	Elem v1, v2;

    	Stack * p = (Stack *) s;
	for(i=0; i<10; i++) {

		/* TBD: Prelevare con StackPop() in v1 */
		v1=StackPop(p);
		/* TBD: Prelevare con StackPop() in v2 */
		v2=StackPop(p);
		printf("Somma: %d\n", v1+v2);

		sleep(3);
	}

	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{

	int rc;
	int i;

	srand(time(NULL));


	Stack * stack = malloc(sizeof(Stack));
       	/* TBD: Creare un oggetto stack */
	StackInit(stack, 4);
	/* TBD: Inizializzare lo stack con StackInit(), 
	 *      indicando "4" come dimensione massima */
	pthread_t threads[6];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for(i=0; i<5; i++) {
		pthread_create(&threads[i], &attr, Inserisci, (void*) stack);
		/* TBD: Creare 5 thread tramite pthread_create(), facendogli
		 *      eseguire la funzione Inserisci(), e passandogli 
		 *      l'oggetto stack come parametro puntatore */

	}
	pthread_create(&threads[5], &attr, Preleva, (void*) stack);
	/* TBD: Creare un thread, facendogli eseguire la funzione Preleva(),
	 *      e passandogli l'oggetto stack come parametro puntatore */



	for(i=0; i<6; i++) {
		pthread_join(threads[i], NULL);
		/* TBD: Effettuare la join con i thread figli */
	}
	StackRemove(stack);
	pthread_attr_destroy(&attr);
	free(stack);
	/* TBD: Disattivare l'oggetto stack con StackRemove() */
}
