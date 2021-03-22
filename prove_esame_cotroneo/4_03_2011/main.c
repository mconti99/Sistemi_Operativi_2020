#include "header.h"
int queue_richiesta, queue_risposta;
int main(){
	//chiave MSG
	
//msgget
int queue_richiesta=msgget(IPC_PRIVATE, IPC_CREAT|0664);
if(queue_richiesta<0){perror("errore msgget"); exit(1);}

int queue_risposta=msgget(IPC_PRIVATE, IPC_CREAT|0664);
if(queue_risposta<0){perror("errore msgget"); exit(1);}

pid_t pid;

for(int i=0;i<3;i++){
pid=fork();
if(pid==0){
	srand(time(NULL)*getpid());
	printf("CLIENTE %d: ", i);
	client();
	printf("TERMINAZIONE CLIENTE %d\n", i);
	exit(0);
}
}
pid=fork();
if(pid==0){
        server();
        exit(0);
}

for(int i=0;i<3;i++) wait(NULL);


msg m;
m.type=2; //TIPO TERMINAZIONE
m.numero1=-1;
m.numero2=-1;
printf("PADRE: invio i numeri speciali\n");
msgsnd(queue_richiesta, &m, sizeof(msg)-sizeof(long), 0);
wait(NULL); //aspetto il server
msgctl(queue_richiesta, IPC_RMID, 0);
msgctl(queue_risposta, IPC_RMID, 0);

	return 0;
}
