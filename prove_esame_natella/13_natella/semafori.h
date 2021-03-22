// Specifica delle funzioni per i semafori
#ifndef _SEMAFORI_H
#define _SEMAFORI_H
// implementa la wait, con semop
void Wait_Sem(int id_sem, int num_sem);

// implementa la signal con semop
void Signal_Sem (int id_sem, int num_sem);

// restituisce il num di processi in attesa su un semaforo
int Queue_Sem (int id_sem, int num_sem);  

// restituisce il valore del semaforo
int Leggi_Sem(int id_sem, int num_sem);
#endif
