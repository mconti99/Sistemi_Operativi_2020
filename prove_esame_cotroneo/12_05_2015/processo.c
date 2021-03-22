#include "procedure.h"

int main(char* argv[], int argc){
key_t key=ftok(".", 'a');
int ds_shm=shmget(key,sizeof(gestionevoli),IPC_CREAT|0664);
srand(time(NULL));

gestionevoli *v;
v=shmat(ds_shm, NULL, 0);
if(v==(void*)-1) {perror("errore shmat"); exit(1);}

int identificativo=(int) argv[1];
inseriscivolo(v, identificativo);
aggiornavolo(v, identificativo, 1000);
aggiornavolo(v, identificativo, 2000);
aggiornavolo(v, identificativo, 1000);
rimuovivolo(v, identificativo);
shmctl(ds_shm, IPC_RMID, 0);
return 0;
}
