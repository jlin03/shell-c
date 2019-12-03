#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char ** parse_args(char * line,int size) {
    char * copy = strdup(line);
    char ** args;
    int i = 0;
    char * iter;
    args = malloc(size*sizeof(char*));
    while((iter = strsep(&copy," ")) != NULL) {
        args[i] = malloc(sizeof(char*));
        strcpy(args[i],iter);
        i++;
    }
    return args;
}

int shell() {
  char input[256];
  while(strcmp(input,"exit") != 0) {

    sleep(1);
    char cwd[4096];
    printf("%s:",getcwd(cwd, sizeof(cwd)));
    fgets(input,256,stdin);
    printf("\n%s",input);
    printf("\n%d",strcmp(input,"exit"));
  }
}

int main() {
  shell();
}
