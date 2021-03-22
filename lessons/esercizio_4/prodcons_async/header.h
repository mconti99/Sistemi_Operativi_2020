#ifndef _header
#define _header
#define MESSAGGIO 1

typedef char msg[40];

typedef struct{
		long tipo;
		msg mess;
} messaggio;

void produttore(int queue, char *m);
void consumatore(int queue);
void printmsginfo(int queue);
#endif


