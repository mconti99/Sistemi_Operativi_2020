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

#define TYPE 1
#define MSG_ERR 2

typedef char stringa[10];
typedef int array[2];
typedef struct{
	long type;
	stringa s;
	array a;
	int var;
}msg;

void generatore(int, int);
void filtro(int, int);
void visualizzatore(int);
void checksum(int, int);
#endif
