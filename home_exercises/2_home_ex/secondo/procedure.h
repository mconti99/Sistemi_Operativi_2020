#define MUTEXL 1
#define SYNCH 0

#define NUM_VOLTE 5

typedef struct{
	int val_1;
	int val_2;
}buffer;

#define FTOK_PATH "./"
#define FTOK_CHAR 'a'

void lettore1(buffer*,int*,  int);
void lettore2(buffer*, int*, int);
void scrittore(buffer*, int);
void InizioLettura(int*, int);
void InizioScrittura(int);
void FineScrittura(int);
void FineLettura(int*, int);
