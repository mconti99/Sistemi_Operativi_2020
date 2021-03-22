#ifndef _SERVERSYNC_H_
#define _SERVERSYNC_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define RTS 1
#define MSG 2 
typedef struct{
	long typeRTS;
	pid_t pid;
}msgRTS;

typedef struct{
	long pid;
	int ID;
}msgOTS;

typedef struct {
    long type;
    int val;
} messaggio;

void receive_sinc(int msg_id, int ok_id, int req_id, messaggio * msg);
void send_sinc(int ok_id, int req_id, messaggio * msg);

#endif
