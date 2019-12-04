#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h>

char ** parse_args(char * line,char * s,int size) {
    char * copy = strdup(line);
    char ** args;
    int i = 0;
    char * iter;
    args = malloc(size*sizeof(char*));
    while((iter = strsep(&copy,s)) != NULL) {
        args[i] = malloc(sizeof(char*));
        strcpy(args[i],iter);
        i++;
    }
    return args;
}

int count_occurence(char * string, char * c) {
  int i = 0;
  int occ = 0;
  while(string[i] != '\0') {
    if(string[i] == c[0]) {
      occ++;
    }
  }
  return occ;
}

int shell() {
  char input[256];
  while(strcmp(input,"exit")-10 != 0) {

    sleep(1);
    char cwd[4096];
    printf("%s:",getcwd(cwd, sizeof(cwd)));
    fgets(input,256,stdin);
    //printf("%d",input[strlen(input)-1]);
    input[(sizeof(input)/sizeof(char))-1] = '\0';
    printf("%s",input);
  //  char ** command = parse_args(input," ",count_occurence(input," ")+1);
  //  pid_t pid = fork();
  //  if(pid == 0) {
  //    if(strcmp(input,"exit")-10 != 0) {
  //      execvp(command[0],command);
  //    }
  //    exit(0);
  //  }
  //  else {
  //    wait(NULL);
    //}


  }
  return 0;
}

int main() {
  shell();
}
