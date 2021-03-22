#include "header.h"

int coda;

int main(){
	init();
	key_t key=ftok(".",'c');
	coda=msgget(key, IPC_CREAT|0664);
	pid_t pid;
	for(int i=0;i<3;i++){
		pid=fork();
		if(pid==0){
			//printf("MAIN: Creo il client %d\n", i);
			execl("./client", "client", (char*)0);
			exit(0);
		}
	}
	pid=fork();
	if(pid==0){
		//printf("MAIN: Creo il Server\n");
		execl("./server", "server", (char*)0);
		exit(0);
	}
	for(int i=0;i<4;i++) wait(NULL);
	removeService();
	msgctl(coda, IPC_RMID, 0);
	return 0;
}
