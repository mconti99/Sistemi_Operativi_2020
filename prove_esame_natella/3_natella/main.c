#include "header.h"

int main(){
	int coda_risposte;
	coda_risposte=msgget(IPC_PRIVATE, IPC_CREAT|0664);

	int coda_richieste;
	coda_richieste=msgget(IPC_PRIVATE, IPC_CREAT|0664);
	pid_t pid;
	srand(time(NULL));
	pid=fork();
	if(pid==0){
		printf("sono il gestore\n");
		Magazzino * ma;
		inizializzazione(ma);
		msg m;
		for(int i=0;i<13;i++){
		msgrcv(coda_richieste, &m, sizeof(msg)-sizeof(long), 0,0);
		if(m.type==FORNITORE){
				ma[m.codice]->quantita=ma[m.codice]->quantita+m.quantita;
		}else if(m.type==CLIENTE1){
			msgc m1;
			m1.type=m.pid;
			for(int i=0;i<10;i++){
				m1.ma[i].costo=ma[i]->costo;
				m1.ma[i].quantita=ma[i]->costo;
			}
			msgsnd(coda_risposte, &m1, sizeof(msgc)-sizeof(long), 0);
		}else if(m.type==CLIENTE2){
			ma[m.codice]->quantita--;
			msgc1 x;
			x.type=m.pid;
			x.quantita=m.quantita;
			msgsnd(coda_risposte, &x, sizeof(msgc1)-sizeof(long), 0);
		}
		}
		exit(0);
	}

	for(int i=0;i<i<2;i++){
	pid=fork();
	if(pid==0){
		printf("sono il fornitore %d\n", i);
		msg m;
		m.quantita=(rand()%5)+1;
		m.codice=(rand()%5)+1;
		m.type=FORNITORE;
		msgsnd(coda_richieste,&m,sizeof(msg)-sizeof(long),0);
		sleep(2);
		printf("seconda fornitura..\n");
                m.quantita=(rand()%5)+1;
                m.codice=(rand()%5)+1;
                m.type=FORNITORE;
                msgsnd(coda_richieste,&m,sizeof(msg)-sizeof(long),0);
		exit(0);

	}
	}
	for(int i=0;i<3;i++){
		pid=fork();
		if(pid==0){
			printf("sono il cliente %d\n", i);
			msg m;
			m.pid=getpid();
			m.type=CLIENTE1;
			msgsnd(coda_richieste, &m, sizeof(msg)-sizeof(long), 0);
			msgc x;
			msgrcv(coda_risposte, &x, sizeof(msgc)-sizeof(long), getpid(), 0);
			sleep(1);
			m.type=CLIENTE2;
			m.codice=(rand()%5)+1;
			msgsnd(coda_richieste, &m, sizeof(msg)-sizeof(long), 0);
			msgc1 y;
			msgrcv(coda_risposte, &y, sizeof(msgc1)-sizeof(long), getpid(), 0);
                        m.codice=(rand()%5)+1;
                        msgsnd(coda_richieste, &m, sizeof(msg)-sizeof(long), 0);
                        msgrcv(coda_risposte, &y, sizeof(msgc1)-sizeof(long), getpid(), 0);
			exit(0);
		}
	for(int i=0;i<6;i++)wait(NULL);
	msgctl(coda_risposte, IPC_RMID, 0);
	msgctl(coda_richieste, IPC_RMID, 0);
	return 0;
}
}
