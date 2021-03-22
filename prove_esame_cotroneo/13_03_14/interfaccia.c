#include "header.h"

int main(){
	key_t key=ftok(".", 'a');
	s1=msgget(key, IPC_CREAT|0664);
	key_t key2=ftok(".", 'b');
	s2=msgget(key, IPC_CREAT|0664);
	pid_t pid;
	pid=fork();
	if(pid==0){
		interfaccia(s1, s2);
	}	
	wait(NULL);
	msgctl(s1, IPC_RMID, 0);
	msgctl(s2, IPC_RMID, 0);
	return 0;
}
