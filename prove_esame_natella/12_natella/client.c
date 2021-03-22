#include "header.h"

int main(){
	init();
        key_t key=ftok(".",'c');
        coda=msgget(key, IPC_CREAT|0664);
	//printf("MAIN CLIENT: Eseguo la funzione client()\n");
	client();
	return 0;
}
