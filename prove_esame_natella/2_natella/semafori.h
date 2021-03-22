// Specifica delle funzioni per i semafori
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// implementa la wait, con semop
void Wait_Sem(int id_sem, int num_sem);

// implementa la signal con semop
void Signal_Sem (int id_sem, int num_sem);

// restituisce il num di processi in attesa su un semaforo
int Queue_Sem (int id_sem, int num_sem);  

// restituisce il valore del semaforo
int Leggi_Sem(int id_sem, int num_sem);
