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

#define RTS 2
#define OTS 3
extern int coda;

typedef struct{
	long pid;
	int numero1;
	int numero2;
}msg;

void removeService();
void init();
void client();
void * receiver(void *);

#endif
