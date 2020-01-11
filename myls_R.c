#include "myls.h"

void list_Recurse(char *path){

	list_short(path);

	DIR *dir = opendir(path);

	if(dir == NULL){
		error_printf("opendir");
	}
	
	struct dirent *p;

	while((p=readdir(dir))!=NULL){
		if(p->d_name[0]!='.' && p->d_type == DT_DIR){
			char new_p[100];
			char sep[1];
			sep[0] = '/';
			strcpy(new_p,path);
			strncat(new_p,sep,1);
			strcat(new_p,p->d_name);
			printf("\n\n%s \n",new_p);
			list_Recurse(new_p);
		}
	}
}
