#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

main(int argc, char *argv[]){
	int fd = open("/dev/input/mice",O_RDONLY);
	char buf[1024];
	int n;
	int i;

	if(fd != -1){
		while((n = read(fd,buf,1024))>0){
			for(i=0;i<n;i++){	
				printf("%d",buf[i]);
			}
			printf("\n");
		}
	}
	else{
		perror("can't open");
		exit(1);
	}
	close(fd);
}
