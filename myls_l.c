#include "myls.h"
#include <dirent.h>

// deal with errors
void error_printf(const char* funname){
	perror(funname);
	exit(1);
}

// read file
void list_dir(const char* pathname){
	DIR* dir = opendir(pathname);
	if(dir == NULL){
		error_printf("opendir");
	}
	
	int ch = chdir(pathname);

	if(ch == -1) error_printf("chdir");

	struct dirent *p;
	while((p = readdir(dir))!=NULL){
		char *filename = p->d_name; // file name
		struct stat file_message = {};// define struct variable
		int stat = lstat(filename,&file_message);// get file info
		if(stat == -1){
			printf("%s error!",filename);
		}
		else {
			if((strncmp(filename,".",1)!=0) && (strncmp(filename,"..",2)!=0)) // don't print . and .. dir
			list_message(filename , &file_message); 
		}
	}
	closedir(dir);
}

void list_message(char *filename, struct stat *file_message){
	file_type(file_message);//type
	file_power(file_message);//power
	printf("%d ", file_message->st_nlink);//link
	file_id(file_message);
	printf("%5ld ", file_message->st_size);//size
	file_mtime(file_message);//time
	printf("%s", filename);//name
	if(S_ISLNK(file_message->st_mode)) link_printf(filename); // if soft link, go into
	puts("");
}

void file_type(struct stat* file_message){
	mode_t mode = file_message->st_mode;
	
	if (S_ISREG(mode)) printf("-");
	else if(S_ISDIR(mode)) printf("d");
	else if(S_ISCHR(mode)) printf("c");
	else if(S_ISBLK(mode)) printf("b");
	else if(S_ISFIFO(mode)) printf("p");
	else if(S_ISLNK(mode)) printf("l");
	else printf("s");
}

void file_power(struct stat *file_message){
	mode_t mode = file_message->st_mode;

	printf("%c",mode&S_IRUSR? 'r':'-');
	printf("%c",mode&S_IWUSR? 'w':'-');
	printf("%c",mode&S_IXUSR? 'x':'-');

	printf("%c",mode&S_IRGRP? 'r':'-');
	printf("%c",mode&S_IWGRP? 'w':'-');
	printf("%c",mode&S_IXGRP? 'x':'-');
	
	printf("%c",mode&S_IXOTH? 'r':'-');
	printf("%c",mode&S_IXOTH? 'w':'-');
	printf("%c ",mode&S_IXOTH? 'x':'-');
}
	
void file_id(struct stat *file_message){
	struct passwd *pwd;
	pwd = getpwuid(file_message->st_uid);
	printf("%s ",pwd->pw_name);

	struct group *grp;
	grp = getgrgid(file_message->st_gid);
	printf("%s ",grp->gr_name);
}

void file_mtime(struct stat* file_message){
	struct tm* t = localtime(&file_message->st_mtime);
	printf("%2dM %2d %02d:%02d ",t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min);

}

void link_printf(char *filename){
	char buf[1024] = "123";

	if(0 == readlink(filename,buf,sizeof(buf))){
		error_printf("readlink");
	}
	printf("-> %s ", buf);
}

void list_short(char *path){
	DIR *dir = opendir(path);
	if(dir == NULL){
		error_printf("opendir");
	}
	
	struct dirent *p;

	while((p=readdir(dir))!=NULL){
		if(p->d_name[0]!='.'){
			printf("%s ",p->d_name);
		}
	}
	printf("\n");
	closedir(dir);
}
