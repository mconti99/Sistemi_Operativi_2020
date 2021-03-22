#define REQUEST_TO_SEND 1
#define OK_TO_SEND 2
#define MESSAGGIO 3

typedef char msg[40];

typedef struct{
	long tipo;
	msg mess;
}messaggio;

void receivebloc(messaggio *, int, int);
void sendsincr(messaggio*, int);
void initservicequeues();
void removeservicequeues();

void produttore(int queue, char *);
void consumatore(int queue);

