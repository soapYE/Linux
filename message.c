#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define MSGKEY 75
struct msgform{
	long mtype;
	char mtext[1000];
} msg;

int msgqid;

void getMessage();

int child;
main(){
	while((child=fork())==-1);
	if(child==0){
		msgqid = msgget(MSGKEY,0777|IPC_CREAT);
		sprintf(msg.mtext,"hello,world!");
		msg.mtype = 1;
		msgsnd(msgqid,&msg,1024,0);
		printf("child send message\n");
		exit(0);
	}
	else{
		printf("parent waiting\n");
		getMessage();
	//	msgqid = msgget(MSGKEY,0777|IPC_CREAT);
	//	msgrcv(msgqid,&msg,1030,0,0);
	//	printf("Got message: %s\n",msg.mtext);
	//	printf("message type: %d\n",msg.mtype);
	//	msgctl(msgqid,IPC_RMID,0);
	//	exit(0);
	}
}

void getMessage(){
	wait(0);
	msgqid = msgget(MSGKEY,0777|IPC_CREAT);
	msgrcv(msgqid,&msg,1030,0,0);
	printf("parent got message: %s\n",msg.mtext);
	printf("message type: %d\n",msg.mtype);
	msgctl(msgqid,IPC_RMID,0);
	exit(0);
}
