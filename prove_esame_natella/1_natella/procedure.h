#ifndef _PROCEDURE_H
#define _PROCEDURE_H

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
#define N 5
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX 2 

#define FTOK_PATH "."
#define FTOK_CHAR 'a'
#define FTOK_CHAR1 'b'

typedef struct{
  int elementi[N];
  int testa;
  int coda;
  int riemp;
} BufferCircolare;

void produci_elemento(int sem_id, BufferCircolare* buf);
void consuma_elementi(int sem_id, BufferCircolare* buf);
#endif
