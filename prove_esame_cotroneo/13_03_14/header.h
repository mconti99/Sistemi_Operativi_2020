#ifndef _HEADER_H
#define _HEADER_H

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
#include <sys/msg.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

#define RTS 10
#define OTS 11

#define AVVIO_PREPARAZIONE 1
#define AVVIO_ROTAZIONE 2
#define INTERRUZIONE_ROTAZIONE 3
#define AVVIO_RISCALDAMENTO 4
#define AGGIORNAMENTO_TEMPERATURA 5
#define INTERRUZIONE_RISCALDAMENTO 6
#define FINE 7
typedef struct{
	long tipo;
	int temperatura;
}msg;
void init();
void removeService();
void interfaccia(int s1, int s2);
void controllore(int s1,int s2, int s3, int s4, int s5);
void mixer(int s3);
void termostato(int s4, int s5);

typedef enum {false, true} bool;

#endif
