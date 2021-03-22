#include "procedure.h"

int main(){
key_t key=ftok(".", 'a');
int ds_shm=shmget(key,sizeof(gestionevoli) ,IPC_CREAT|0664);


gestionevoli *v;
v=shmat(ds_shm, NULL, 0);
if(v==(void*)-1) {perror("errore shmat"); exit(1);}

init_monitor(&(v->m), 1);
v->numero_occupati=0;
v->numero_liberi=3;
pid_t pid;
for(int i=0;i<5;i++){
pid=fork();
if(pid==0){
	funzione(v, i);
	exit(0);
}else if(pid<0){
	perror("errore fork");
	exit(1);
}
}
for(int i=0;i<5;i++) wait(NULL);
remove_monitor(&(v->m));
shmctl(ds_shm, IPC_RMID, 0);
//deallocazione shm
return 0;
}
