#include "header.h"
static int s31, s32, s41, s42;
void init(){
	key_t k1=ftok(".", 'a');
	s31=msgget(k1, IPC_CREAT|0664);
	key_t k2=ftok(".", 'b');
	s32=msgget(k2, IPC_CREAT|0664);
	key_t k3=ftok(".", 'c');
	s41=msgget(k3, IPC_CREAT|0664);
	key_t k4=ftok(".", 'd');
	s42=msgget(k4, IPC_CREAT|0664);
}
void removeService(){
	msgctl(s31, IPC_RMID, 0);
	msgctl(s32, IPC_RMID, 0);
	msgctl(s41, IPC_RMID, 0);
	msgctl(s42, IPC_RMID, 0);
}
void interfaccia(int s1, int s2){
	msg m;
	long tipo;
	printf("Dimmi che devo fare\n");
	scanf("%ld", &tipo);
	m.tipo=tipo;
	if(m.tipo==AVVIO_PREPARAZIONE)
	msgsnd(s1, &m, sizeof(msg)-sizeof(long), 0);
	msg m1;
	bool finisci;
	while(finisci==false){
		msgrcv(s2, &m1, sizeof(msg)-sizeof(long), 0, 0);
		if(m1.tipo==AVVIO_ROTAZIONE) printf("AVVIO ROTAZIONE\n");
		else if(m1.tipo==INTERRUZIONE_ROTAZIONE) printf("INTERRUZIONE ROTAZIONE\n");
		else if(m1.tipo==AVVIO_RISCALDAMENTO) printf("AVVIO RISCALDAMENTO\n");
		else if(m1.tipo==INTERRUZIONE_RISCALDAMENTO) printf("INTERRUZIONE RISCALDAMENTO\n");
		else if(m1.tipo==AGGIORNAMENTO_TEMPERATURA) printf("AGGIORNAMENTO TEMPERATURA ---> %d\n", m1.temperatura);
		else finisci=true;
	}
	exit(0);
}

void controllore(int s1,int s2, int s3, int s4, int s5){
	msg m;	
	msgrcv(s1, &m, sizeof(msg)-sizeof(long), AVVIO_PREPARAZIONE, 0);
	msg m1, m2, m3;
	m1.tipo=RTS;
	msgsnd(s31, &m1, sizeof(msg)-sizeof(long), 0);
	msgrcv(s32, &m2, sizeof(msg)-sizeof(long), OTS, 0);
	m3.tipo=AVVIO_ROTAZIONE;
	msgsnd(s3, &m3, sizeof(msg)-sizeof(long), 0);
	msgsnd(s2, &m3, sizeof(msg)-sizeof(long), 0);
	sleep(3);
        msgsnd(s31, &m1, sizeof(msg)-sizeof(long), 0);
        msgrcv(s32, &m2, sizeof(msg)-sizeof(long), OTS, 0);
        m3.tipo=INTERRUZIONE_ROTAZIONE;
        msgsnd(s3, &m3, sizeof(msg)-sizeof(long), 0);
	msgsnd(s2, &m3, sizeof(msg)-sizeof(long), 0);
	msgsnd(s41, &m1, sizeof(msg)-sizeof(long), 0);
	msgrcv(s42, &m2, sizeof(msg)-sizeof(long), OTS, 0);
	m3.tipo=AVVIO_RISCALDAMENTO;
	m3.temperatura=15;
	msgsnd(s4, &m3, sizeof(msg)-sizeof(long), 0);
	msgsnd(s2, &m3, sizeof(msg)-sizeof(long), 0);
	while(m3.temperatura<50){
		msgrcv(s5, &m3, sizeof(msg)-sizeof(long), AGGIORNAMENTO_TEMPERATURA, 0);
		msgsnd(s2, &m3, sizeof(msg)-sizeof(long), 0);
	}
	msgsnd(s41, &m1, sizeof(msg)-sizeof(long), 0);
	msgrcv(s42, &m2, sizeof(msg)-sizeof(long), OTS, 0);
	m3.tipo=INTERRUZIONE_RISCALDAMENTO;
	msgsnd(s4, &m3, sizeof(msg)-sizeof(long), 0);
	msgsnd(s2, &m2, sizeof(msg)-sizeof(long), 0);

	msg m4;
	m4.tipo=FINE;
	msgsnd(s2, &m4, sizeof(msg)-sizeof(long), 0);
	msgsnd(s31, &m1, sizeof(msg)-sizeof(long), 0);
        msgrcv(s32, &m2, sizeof(msg)-sizeof(long), OTS, 0);
        msgsnd(s3, &m4, sizeof(msg)-sizeof(long), 0);

	msgsnd(s41, &m1, sizeof(msg)-sizeof(long), 0);
        msgrcv(s42, &m2, sizeof(msg)-sizeof(long), OTS, 0);
        msgsnd(s4, &m4, sizeof(msg)-sizeof(long), 0);

}

void mixer(int s3){
	msg m1, m2, m3;
	msgrcv(s31, &m1, sizeof(msg)-sizeof(long), RTS, 0);
	m2.tipo=OTS;
	msgsnd(s32, &m2, sizeof(msg)-sizeof(long), 0);
	msgrcv(s3, &m3, sizeof(msg)-sizeof(long), AVVIO_ROTAZIONE, 0);
	
	msgrcv(s31, &m1, sizeof(msg)-sizeof(long), RTS, 0);
	msgsnd(s32, &m2, sizeof(msg)-sizeof(long), 0);
	msgrcv(s3, &m3, sizeof(msg)-sizeof(long), INTERRUZIONE_ROTAZIONE, 0);
	bool finisci;
	while(finisci==false){
		msgrcv(s31, &m1, sizeof(msg)-sizeof(long), RTS, 0);
		msgsnd(s32, &m2, sizeof(msg)-sizeof(long), 0);
		msgrcv(s3, &m3, sizeof(msg)-sizeof(long), FINE, 0);
		finisci=true;
	}
	exit(0);
}

void termostato(int s4, int s5){
	msg m1, m2, m3;
	msgrcv(s41, &m1, sizeof(msg)-sizeof(long), RTS, 0);
	m2.tipo=OTS;
	msgsnd(s42, &m2, sizeof(msg)-sizeof(long), 0);
	msgrcv(s4, &m3, sizeof(msg)-sizeof(long), AVVIO_RISCALDAMENTO, 0);
	long terminazione =0;
	int rc=0;
	while(terminazione!=INTERRUZIONE_RISCALDAMENTO){
		m3.temperatura=m3.temperatura + 3;
		m3.tipo= AGGIORNAMENTO_TEMPERATURA;
		msgsnd(s5, &m3, sizeof(msg)-sizeof(long), 0);
		rc=msgrcv(s41, &m1, sizeof(msg)-sizeof(long), RTS, IPC_NOWAIT);
		if(rc!=-1){
			msgsnd(s42, &m2, sizeof(msg)-sizeof(long), 0);
			msgrcv(s4, &m3, sizeof(msg)-sizeof(long), INTERRUZIONE_RISCALDAMENTO, 0);
			terminazione = m3.tipo;
		}
	}
	bool finisci;
        while(finisci==false){
                msgrcv(s41, &m1, sizeof(msg)-sizeof(long), RTS, 0);
                msgsnd(s42, &m2, sizeof(msg)-sizeof(long), 0);
                msgrcv(s4, &m3, sizeof(msg)-sizeof(long), FINE, 0);
                finisci=true;
        }
        exit(0);


}
