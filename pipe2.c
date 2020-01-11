#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void read1(),read2();

int p1,p2;	
int fd[2];
char OutPipe[100],InPipe[100];
main(){
	pipe(fd);
	
	while((p1 = fork())==-1);
	if(p1 == 0){
		signal(SIGUSR1,read1);
		pause();
	}
	else{
		while((p2 = fork())==-1);
		if(p2 == 0){
			signal(SIGUSR1,read2);
			pause();
		}
		else{
			sprintf(OutPipe,"parent process is sending message!");
			write(fd[1],OutPipe,50);
			sleep(5);
			kill(p1,SIGUSR1);
			sprintf(OutPipe,"parent process is sending message!");
			write(fd[1],OutPipe,50);
			sleep(5);
			kill(p2,SIGUSR1);
			wait(0);
			wait(0);
			exit(0);
		}
	}
}

void read1(){
	lockf(fd[0],1,0);
	read(fd[0],InPipe,50);
	printf("process 1 is reading: %s\n",InPipe);
	lockf(fd[0],0,0);
	exit(0);
}

void read2(){
	lockf(fd[0],1,0);
	read(fd[0],InPipe,50);
	printf("process 2 is reading: %s\n",InPipe);
	lockf(fd[0],0,0);
	exit(0);
}
