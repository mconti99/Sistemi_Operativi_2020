#include "processi.h"
#include "semafori.h"

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int inizializza_semafori()
{
    key_t k_sem = IPC_PRIVATE;
    int sem_id =semget(k_sem, 1, IPC_CREAT|0664); /* TBD: usare semget() per allocare un vettore,
                  *      con un singolo semaforo "mutex" */

    if (sem_id < 0)
    {
        perror("Impossibile creare il semaforo per la mutua esclusione");
        exit(1);
    }

    /* Valore iniziale: 1 (mutua esclusione) */
    semctl(sem_id,0,SETVAL,1);


    /* TBD: inizializzare il mutex */

    return sem_id;
}

void figlio(int *vettore,
            int *buffer,
            int sem_id,
            int elemento_iniziale,
            int qta_elementi)
{

    /* TBD: aggiungere dentro questa funzione delle chiamate a
     *      Wait_Sem() e Signal_Sem() per creare una sezione critica
     *      e realizzare la mutua esclusione */
    int minimo = INT_MAX;

    for (int i = elemento_iniziale; i < elemento_iniziale + qta_elementi; i++)
    {

        if (vettore[i] < minimo)
        {

            minimo = vettore[i];
        }
    }

    printf("Figlio: Il minimo locale (di un processo figlio)  è %d\n", minimo);
    Wait_Sem(sem_id,0);
    if (minimo < *buffer)
    {

        *buffer = minimo;
    }
    Signal_Sem(sem_id,0);
}


void padre(int *buffer,
           int sem_id)
{

    /* Attesa terminazione processi figli */

    /* TBD: Utilizzare wait() per attendere la terminazione dei 10 figli */
for(int i=0;i<10;i++) wait(NULL);
    

    /* Risultato finale */
    Wait_Sem(sem_id,0);
    printf("Padre: Il valore minimo assoluto è: %d\n", *buffer);
   Signal_Sem(sem_id,0);
}
