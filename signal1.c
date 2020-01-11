# include<stdio.h>
# include<signal.h>
# include<unistd.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/wait.h>

int wait_mark;

void waiting(),stop();
void main(){
	int p1,p2;
	while((p1=fork())==-1);
	if(p1>0){
		while((p2=fork())==-1);
		if(p2>0){
			signal(SIGINT,stop);
			wait_mark=1;
			waiting();
			kill(p1,10);
			kill(p2,12);
			wait(0);
			wait(0);
			printf("parent process is killed!\n");
			exit(0);
		}
		else{
			wait_mark=1;
			signal(12,stop);
			waiting();
			lockf(1,1,0);
			printf("child process 2 is killed by parent!\n");
			lockf(1,0,0);
			exit(0);
		}
	}
	else{
		wait_mark=1;
		signal(10,stop);
		waiting();
		lockf(1,1,0);
		printf("child process 1 is killed by parent!\n");
		lockf(1,0,0);
		exit(0);
	}
}
void waiting(){
	while(wait_mark!=0);
}
void stop(){
	wait_mark=0;
}
