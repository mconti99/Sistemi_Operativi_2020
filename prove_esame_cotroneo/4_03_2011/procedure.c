#include "header.h"
int queue_richiesta, queue_risposta;
void client(){
	msg m;
	msg1 m1;
	m.type=getpid();

		for(int i=0;i<5;i++){
			m.numero1=rand()%101;
                	m.numero2=rand()%101;
			printf("RICHIESTA CLIENT, numero %d: inviata (%d, %d) [PID=%ld]\n\n", i, m.numero1, m.numero2, m.type);
			msgsnd(queue_richiesta, &m, sizeof(msg)-sizeof(long), 0);
			printf("CLIENT [%d]: ho inviato richiesta e aspetto risposta dal server\n", getpid());
			msgrcv(queue_risposta, &m1, sizeof(msg1)-sizeof(long), getpid(), 0);
			printf("CLIENT [%d]: risposta %d ricevuta (%d) [PID=%ld]\n\n",getpid(),i,  m1.prod, m.type);
		}
}

void server(){

	//inizializzazione attr
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t threads[15];
	struttura * s= malloc(sizeof(struttura));
	pthread_mutex_init(&s->mutex, NULL);
	s->m.numero1=0;
	s->m.numero2=0;
	s->m.type=0;
	for(int j=0;j<16;j++){
	printf("SERVER: aspetto di ricevere dal client\n");
	msgrcv(queue_richiesta,&s->m, sizeof(msg)-sizeof(long), 0, 0);
	printf("SERVER: numeri che ho ricevuto %d %d dal CLIENT %ld\n",s->m.numero1, s->m.numero2, s->m.type);
	if(s->m.type==2){
		printf("SERVER TERMINA\n");
		for(int i=0;i<15;i++){
			pthread_join(threads[i], NULL);
		}	
		pthread_attr_destroy(&attr);
		pthread_mutex_destroy(&s->mutex);
		free(s);
		pthread_exit(0);
	}
	else{
		//creazione thread
		printf("SERVER: Creo il thread %d\n", j);
		pthread_create(&threads[j], &attr, produttore, (void *) s);
		}
	}	
}	

void * produttore(void * p){
	struttura * s= (struttura *) p;
	msg1 m1;
	m1.prod= s->m.numero1 * s->m.numero2;
	m1.type= s->m.type;
	pthread_mutex_lock(&s->mutex);
	printf("\nPRODUTTORE SERVER: Invio del calcolo: %d * %d = %d\n\n",s->m.numero1, s->m.numero2,  m1.prod);
	msgsnd(queue_risposta, &m1, sizeof(msg1)-sizeof(long), 0);
	pthread_mutex_unlock(&s->mutex);
	pthread_exit(0);
}

