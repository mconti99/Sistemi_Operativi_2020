#include "header.h"

int main(){
	init();
        key_t key=ftok(".", 'a');
        int s1=msgget(key, IPC_CREAT|0664);
        key_t key2=ftok(".", 'b');
        int s2=msgget(key, IPC_CREAT|0664);
	key_t key3=ftok(".", 'b');
        int s3=msgget(key, IPC_CREAT|0664);
	key_t key4=ftok(".", 'b');
        int s4=msgget(key, IPC_CREAT|0664);
	key_t key5=ftok(".", 'b');
        int s5=msgget(key, IPC_CREAT|0664);

        pid_t pid;
        pid=fork();
        if(pid==0){
                controllore(s1, s2, s3, s4, s5);
        }
	pid=fork();
	if(pid==0){
		mixer(s3);
	}
	pid=fork();
	if(pid==0){
		termostato(s4, s5);
	}
	for(int i=0;i<3;i++) wait(NULL);
	removeService();
        msgctl(s1, IPC_RMID, 0);
        msgctl(s2, IPC_RMID, 0);
        return 0;
}
~
~
~                
