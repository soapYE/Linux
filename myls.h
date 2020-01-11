#ifndef _MYLS_H_
#define _MYLS_H_

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>
#include<unistd.h>

// deal with error
void error_printf(const char* );

// deal with file
void list_dir(const char* );
void list_message(char* ,struct stat*);

// info of file
void file_type(struct stat*);
void file_power(struct stat*);
void file_id(struct stat*);
void file_mtime(struct stat*);
void link_printf(char*);
void list_short(char*);
void list_Recurse(char*);

#endif
