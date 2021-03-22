#include "header.h"

static int queue1;
static int queue2;
int coda;
void init(){
	key_t key1=ftok(".", 'a');
	key_t key2=ftok(".", 'b');
	queue1=msgget(key1, IPC_CREAT|0664);
	queue2=msgget(key2, IPC_CREAT|0664);
}

void removeService(){
	msgctl(queue1, IPC_RMID, 0);
	msgctl(queue2, IPC_RMID, 0);
}

void client(){
	srand(time(NULL)*getpid());
	msg m;
	msg m1, m2;
	for(int i=0;i<4;i++){
	m.numero1=rand()%11;
	m.numero2=rand()%11;
	m.pid=getpid();
	m1.pid=getpid();
	msgsnd(queue1, &m1, sizeof(msg)-sizeof(long), 0);
	//printf("CLIENTE [%d], elaborazione %d su 3: ho inviato una RTS e aspetto una OTS\n",getpid(),  i);
	msgrcv(queue2, &m2, sizeof(msg)-sizeof(long), getpid(), 0);
	//printf("CLIENTE [%d], elaborazione %d su 3: ho ricevuto la OTS e ora mando il messaggio completo\n", getpid(), i);
	printf("CLIENTE [%d], elaborazione %d su 3: ho inviato un messaggio con VALORI [%d] [%d] e PID [%ld]\n", getpid(),i, m.numero1, m.numero2, m.pid);
	msgsnd(coda, &m, sizeof(msg)-sizeof(long), 0);
	}
}

void * receiver(void * p){
	msg * c = (msg* ) p;
	msg m;
	msg m1, m2;
	for(int i=0;i<5;i++){
	msgrcv(queue1, &m1, sizeof(msg)-sizeof(long), 0, 0);
	//printf("THREAD RECEIVER [%ld], elaborazione %d su 5: ho ricevuto una RTS\n",  syscall(SYS_gettid), i);
	long mypid= m1.pid;
	m2.pid=mypid;
	//printf("THREAD RECEIVER [%ld], elaborazione %d su 5: mando una OTS al pid %ld\n", syscall(SYS_gettid), i, mypid);
	msgsnd(queue2, &m2, sizeof(msg)-sizeof(long), 0);
	//printf("THREAD RECEIVER [%ld], elaborazione %d su 5: ho inviato una OTS e aspetto di ricevere il messaggio completo\n", syscall(SYS_gettid),i);
	msgrcv(coda, &m, sizeof(msg)-sizeof(long), mypid, 0);
	printf("RECEIVER THREAD: ricevo il pid %ld e la somma dei due valore è %d\n", m.pid, m.numero1 + m.numero2);
	}
	pthread_exit(0);
}
