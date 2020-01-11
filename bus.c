#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int child;
int running;

void closeDoor(), openDoor(),shut();
void runBus(),stopBus(),toEnd();

void main(){
	signal(SIGINT,SIG_IGN);
	while((child = fork())==-1);
	if(child == 0){
		signal(SIGQUIT,SIG_IGN);
		running==0;
		while(1==1){
			if(running==0){
				signal(SIGINT,closeDoor);
				signal(SIGUSR1,SIG_IGN);
				signal(SIGUSR2,SIG_IGN);
				pause();
				running = 1;
			}
			else{
				signal(SIGINT,SIG_IGN);
				signal(SIGUSR1,openDoor);
				signal(SIGUSR2,shut);
				pause();
				running = 0;
			}
		}
	}
	else{
		running==0;
		while(1==1){
			if(running==0){
				signal(SIGINT,SIG_IGN);
				signal(SIGUSR1,runBus);
				signal(SIGQUIT,SIG_IGN);
				pause();
				running = 1;
			}
			else{
				signal(SIGINT,stopBus);
				signal(SIGQUIT,toEnd);
				signal(SIGUSR1,SIG_IGN);
				pause();
				running = 0;
			}
		}
	}
}

void closeDoor(){
	lockf(1,1,0);
	printf("close door\n");
	lockf(1,0,0);
	kill(getppid(),SIGUSR1);
}
void openDoor(){
	lockf(1,1,0);
	printf("open door\n");
	lockf(1,0,0);
}

void runBus(){
	lockf(1,1,0);
	printf("run bus\n");
	lockf(1,0,0);
}
void stopBus(){
	lockf(1,1,0);
	printf("stop bus\n");
	lockf(1,0,0);
	kill(child,SIGUSR1);
}

void toEnd(){
	lockf(1,1,0);
	printf("end of route\n");
	lockf(1,0,0);
	kill(child,SIGUSR2);
	wait(0);
	exit(0);
}

void shut(){
	lockf(1,1,0);
	printf("open the door\n");
	lockf(1,0,0);
	exit(0);
}
