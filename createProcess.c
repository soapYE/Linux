#include<stdio.h>

main(){
	int p1,p2;
	while((p1=fork())==-1);
	if(p1==0) printf("i am child 1, my process id is %d\n",getpid()); /*在子进程1*/
	else{
		while((p2=fork())==-1);
		if(p2==0) printf("i am child 2, my process id is %d\n",getpid()); /*在子进程2*/
		else printf("i am father, my process id is %d\n",getpid()); /*在父进程*/
	}
}
