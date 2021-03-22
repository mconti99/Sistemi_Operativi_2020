#define MUTEXL 0
#define SYNCH 1

#define NUM_VOLTE 6
typedef long msg;
typedef struct{
	int numlettori;
	msg messaggio;
}Buffer;

void lettore(int, Buffer *);
void scrittore(int, Buffer*);
