#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#define MSGKEY 75

struct msgform{
	long mtype;
	char mtext[1000];
} msg;
int msgqid;

void server(){
	msgqid = msgget(MSGKEY,0777|IPC_CREAT);
	do{	
		msgrcv(msgqid,&msg,1030,0,0);
		printf("(server)received\n");
	}while(msg.mtype!=1);
	msgctl(msgqid,IPC_RMID,0);
	exit(0);
}

main(){
	server();
}
