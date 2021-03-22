#include "header.h"

int main(){
        key_t key=ftok(".", 'a');
        int id_shm=shmget(key, sizeof(struttura), IPC_CREAT|0664);
        struttura * s = shmat(id_shm ,0, 0);
        key_t key2=ftok(".", 'b');
        int id_sem=semget(key2, 3, IPC_CREAT|0664);
        studente(id_sem, s);
        return 0;
}            
