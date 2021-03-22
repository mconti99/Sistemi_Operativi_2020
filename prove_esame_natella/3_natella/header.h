#ifndef _HEADER_H
#define _HEADER_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/msg.h>
#include <string.h>

#define CLIENTE1 1
#define CLIENTE2 2
#define FORNITORE 3
typedef struct {
    int costo;
    int quantita;
} Magazzino[10];


typedef struct{
        long type;
        int quantita;
        int costo;
	pid_t pid;
	int codice;
}msg;

typedef struct{
        long type;
        Magazzino ma;
}msgc;

typedef struct{
	long type;
	int quantita;//strano
}msgc1;



void inizializzazione(Magazzino*);
#endif
