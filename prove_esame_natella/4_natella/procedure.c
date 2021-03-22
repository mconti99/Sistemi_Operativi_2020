#include "header.h"

void produci(int queue1, int queue2){
	for(int i=0; i<5;i++){
	msg m;
	msg m1;
	m.tipo= MSG;
	m.valore=rand();
	msgrcv(queue2, &m1, sizeof(msg)-sizeof(long), 2, 0);
	msgsnd(queue1, &m, sizeof(msg)-sizeof(long), 0);
	}
}

void consuma(int queue1, int queue2){
	for(int i=0;i<9;i++){
		msg m;
		msgrcv(queue1, &m, sizeof(msg)-sizeof(long),1, 0);
		msg m1;
		printf(" il valore del buffer è %d \n",m->valore);
		m1.tipo=TOK;
		msgsnd(queue2, &m1, sizeof(msg)-sizeof(long), 0);
	}	
}
