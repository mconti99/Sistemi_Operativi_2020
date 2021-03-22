#ifndef _PROCEDURE_H
#define _PROCEDURE_H

#define MUTEXL 0
#define SYNCH 1
#define MUTEXU 2
#define SYNCHU 3
#include <stdio.h>
#include "semafori.h"
#define NMAX 10
#define FTOK_PATH "."
#define FTOK_CHAR 'a'
#define FTOK_CHAR1 'b'
typedef struct{
	int N;
	int a[NMAX][NMAX];
	int numlettori;
	int v;
	int numt;

}buffer;

void generatore(int ds_sem, buffer*);
void elaboratore(int ds_sem, buffer*);
void analizzatore(int ds_sem, buffer*);

#endif
