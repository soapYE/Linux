#include<stdio.h>

main(){
	int b,c,d;
	while((b=fork())==-1);
	if(b==0){
		printf("b: %d  parent: %d\n",getpid(),getppid());
		while((c=fork())==-1);
		if(c==0){	
			printf("c: %d  parent: %d\n",getpid(),getppid());
			while((d=fork())==-1);
			if(d==0){
				printf("d: %d  parent: %d\n",getpid(),getppid());			}
		}
	}
	else printf("a: %d parent: %d\n",getpid(),getppid());
}
