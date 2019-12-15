#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

char ** parse_args(char * line,char * s,int size);
int count_occurence(char * string, char * c);
char * replace_char(char * string, char * c, char * r);
char * remove_trailing(char * string, char * c);
int shell();
void run_line(char * input);
void forkxec(char ** args);
