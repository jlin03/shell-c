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
    i++;
  }
  return occ;
}

char * remove_trailing(char * string, char * c) {
  char * out;
  int i = 0;
  out = malloc(256*sizeof(char*));

  if(string[0] == c[0]) {
    while(string[i] && string[i] == c[0]) {
      if(string[i+1] && string[i+1] != c[0]) {
        strcpy(out,&string[i+1]);
        break;
      }
      i++;
    }
  }
  else {
    strcpy(out,&string[0]);
  }

  i = strlen(out)-1;
  if(out[i] == c[0]) {
    while(out[i] && out[i] == c[0]) {
      out[i] = '\0';
      i--;
    }
  }
  return out;

}

int shell() {
  char input[256];
  while(strcmp(input,"exit") != 0) {

    sleep(1);
    char cwd[4096];
    printf("%s:",getcwd(cwd, sizeof(cwd)));
    fgets(input,256,stdin);
    strtok(input, "\n");
    //printf("%d",input[strlen(input)-1]);
    //printf("%s",input);
    //printf("%d",strcmp(input,"exit"));
    //printf("%d",count_occurence(input,";")+1);
    char ** command_list = parse_args(input,";",count_occurence(input,";")+1);
    int cmd_amt = count_occurence(input,";")+1;
    int i = 0;
    //printf("\n%s",command_list[0]);
    //printf("\n%s",command_list[1]);
    //printf("\n%ld",sizeof(command_list)/sizeof(char*));

    for(int i = 0; i < cmd_amt; i++) {
      char * command = remove_trailing(command_list[i]," ");
      char ** args = parse_args(command," ",count_occurence(command," ")+1);
      pid_t pid = fork();
      if(pid == 0) {
        if(strcmp(command,"exit") != 0 && strcmp(command,"cd") != 0) {
          execvp(args[0],args);
        }
        exit(0);
      }
      else {
        if(strcmp(args[0],"cd") == 0) {
          if(sizeof(args)/sizeof(char*) == 1) {
            chdir(getenv("HOME"));
          }
          else {
            printf("\n%s",args[1]);
            chdir(args[1]);
          }
        }
        wait(NULL);
      }
    }


  }
  return 0;
}

int main() {
  shell();
}
