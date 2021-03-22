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
#include "semafori.h"
#include <string.h>
#define NMAX 16

#define MUTEXL 0
#define SYNCH 1

typedef struct{
	int N;
	char str[NMAX];
	int numlettori;
}buffer;

#define FTOK_PATH "."
#define FTOK_CHAR 'a'
#define FTOK_CHAR1 'b'
#endif
