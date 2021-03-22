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

#define MSG 1
#define TOK 2
typedef struct{
	long type;
	int valore;
}msg;

void produci(int, int);
void consuma(int, int);
#endif
