#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

main(int account, char **para){
	int fin,fout;
	char buf[1024]={};
	int n;
	int exist = 0;
	
	if(account!=3){
		printf("Usage :mycp filename target\n");
         	exit(1);
	}
	if((fin=open(*(para+1),O_RDONLY))==-1){
		perror("file doesn't exist");
		exit(1);
	}
	if((fout=open(*(para+2),O_WRONLY|O_CREAT|O_EXCL,0644))==-1){
		exist = 1;
	}
	
	if(exist == 1){
		fout = open(*(para+2),O_WRONLY);
		ftruncate(fout,0);
	}
	
	while(1){
		n = read(fin,buf,sizeof(buf));
		if(n==-1){
			perror("read");
			exit(1);
		}
		if(n==0){
			break;
		}
		write(fout,buf,n);
	}

	close(fin);
	close(fout);
}
