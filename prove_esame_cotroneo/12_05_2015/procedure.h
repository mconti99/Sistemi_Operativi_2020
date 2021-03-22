#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "monitor.h"

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2
#define VARCOND_PRODUTTORI 0 
typedef struct{
	int identificativo;
	int quota;
}volo;

typedef struct{
	volo vettore_voli[3];
	int vettore_stato[3];
	Monitor m;
	int numero_occupati;
	int numero_liberi;
}gestionevoli;

void inseriscivolo(gestionevoli *g, int identificativo);
void rimuovivolo(gestionevoli *g, int identificativo);
void aggiornavolo(gestionevoli *g, int identificativo, int quota);
void funzione(gestionevoli *g, int i);

