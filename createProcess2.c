#include <stdio.h>
#define MAX 10

main(){
	int p1, p2, i;
	while((p1=fork())==-1);
	if(p1==0)
		for(i=0;i<MAX;i++) printf("daughter %d\n",i);
	else{
		while((p2=fork())==-1);
		if(p2==0)
			for(i=0;i<MAX;i++) printf("son %d\n",i);
		else{
			for(i=0;i<MAX;i++) printf("parents %d\n",i);
		}
	}
	
}
