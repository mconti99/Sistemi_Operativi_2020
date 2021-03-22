#define "header.h"

int main(){
	int coda_messaggi;
	coda_messaggi=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	int coda_token;
	coda_token=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	pid_t pid;
	msg m;
	m.tipo=TOK;
	for(int i=0;i<9;i++)
		msgsnd(coda_messaggi, &m, sizeof(msg)-sizeof(long), 0);
	for(int i=0;i<4;i++){

		pid=fork();
		if(pid==0){
			srand(time(NULL)*getpid());
			produci(coda_messaggi, coda_token);
			exit(0);
		}
	}

	for(int i=0;i<2;i++){
		pid=fork();
		if(pid==0){
			sleep(1);
			consuma(coda_messaggi, coda_token);
			exit(0);
		}
	}
	for(int i=0;i<11;i++) wait(NULL);

	msgctl(coda_messaggi, IPC_RMID, 0);
	msgctl(coda_token, IPC_RMID, 0);
	return 0;
}
