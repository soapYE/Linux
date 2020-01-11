# include<stdio.h>
# include<signal.h>
# include<unistd.h>
# include<stdlib.h>
int pid1, pid2;
int endFlag = 0;

void IntDelete(){
	kill(pid1,10);
	kill(pid2,12);
	endFlag = 1;
}

void Int1(){
	printf("child process 1 is killed by parent!\n");
	exit(0);
}
void Int2(){
	printf("child process 2 is killed by parent!\n");
	exit(0);
}

main(){
	int exitcode;
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	while((pid1=fork())==-1);
	if(pid1==0){
		signal(SIGUSR1,Int1);
		pause();
		exit(0);
	}
	else{
		while((pid2=fork())==-1);
		if(pid2==0){
			signal(SIGUSR2,Int2);
			pause();
			exit(0);
		}
		else{
			signal(SIGINT,IntDelete);
			waitpid(-1,&exitcode,0);
			waitpid(-1,&exitcode,0);
			printf("parent process is killed\n");
			exit(0);
		}
	}
}
