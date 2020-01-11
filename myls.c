#include "myls.h"

main(int ac, char **av){
	DIR *dp;
	struct dirent *p;
	if(1==ac){
		list_short(".");
	}
	else if(ac == 2){
		if(strcmp(av[1],"-l")==0){
			list_dir(".");
		}
		else if(strcmp(av[1],"-R")==0){
			list_Recurse(".");
		}
		else{
			list_short(av[1]);
		}
	}
	else{
		if(strcmp(av[1],"-l")==0){
			list_dir(av[2]);
		}
		else if(strcmp(av[1],"-R")==0){
			list_Recurse(av[2]);
		}
		else{
			perror("usage: ls -l path or ls -R path or ls path");
		}
	}
}
