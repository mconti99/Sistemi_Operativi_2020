#ifndef _PROCEDURE_H
#define _PROCEDURE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int Wait_Sem(int id_sem, int numsem);
int Signal_Sem(int id_sem, int numsem);

#endif