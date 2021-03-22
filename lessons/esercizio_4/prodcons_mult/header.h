#ifndef _P_H
#define _P_H

#define P1 1
#define P2 2

#define FTOK_PATH_Q "."
#define FTOK_CHAR_Q 'a'

struct msg_calc{
	long processo;
	float numero;
};//in questo caso non uso il typedef, quindi dovrò andare a dichiare sempre struct



//genera un valore float nell'intervallo [i_dx, i_sx]
float generafloat(int i_dx, int i_sx);

#endif
