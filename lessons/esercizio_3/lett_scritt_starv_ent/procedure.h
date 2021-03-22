#ifndef _HEADER_H
#define _HEADER_H

#define NUM_VOLTE 3
#define SYNCH 0
#define MUTEXS 1
#define MUTEXL 2
#define MUTEX 3

typedef long msg;

typedef struct{
	int numlettori;
	int numscrittori;
	msg messaggio;
}Buffer;

void InizioLettura(int, Buffer*);
void FineLettura(int, Buffer*);
void InizioScrittura(int, Buffer*);
void FineScrittura(int, Buffer*);
void lettore(int, Buffer*);
void scrittore(int, Buffer*);

#endif
