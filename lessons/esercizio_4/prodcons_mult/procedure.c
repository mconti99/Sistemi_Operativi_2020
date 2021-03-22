#include <time.h>
#include <stdlib.h>

float generafloat(int i_sx, int i_dx){
	float x= (float) rand()/(float)RAND_MAX;
	return i_sx+(i_dx-i_sx)*x;
}
