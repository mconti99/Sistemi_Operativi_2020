#ifndef _HEADER_H
#define _HEADER_H

#define FTOK_PATH "."

#define TYPE 1

struct msg{
	long tipo;
	char message[20]; //messaggio effettivo
};


void sender(int, int, int, int);
void receiver(int);

#endif
