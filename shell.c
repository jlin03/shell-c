// > redirect stdout to file (overwrite)
// >> redirect stdout to file (append)
// 2> redirect stderror to file
// &> redirect stdout and stderror

// < redirect stdin from a file



#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

void forkxec(char ** args);
void run_line(char * input);

char ** parse_args(char * line,char * s,int size) {
    char * copy = strdup(line);
    char ** args;
    int i = 0;
    char * iter;
    while((iter = strsep(&copy,s)) != NULL) {
        args[i] = malloc(sizeof(char)*32);
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

char * replace_char(char * string, char * c, char * r) {
  int i = 0;
  while(string[i] != '\0') {
    if(string[i] == c[0]) {
      string[i] = r[0];
    }
    i++;
  }
  return string;
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
  char input[1024];
  while(strcmp(input,"exit") != 0) {
    char cwd[4096];
    printf("\n%s:",getcwd(cwd, sizeof(cwd)));
    fgets(input,sizeof(char)*1024,stdin);
    strtok(input, "\n");
    //printf("%d",input[strlen(input)-1]);
    //printf("%s",input);
    //printf("%d",strcmp(input,"exit"));
    //printf("%d",count_occurence(input,";")+1);
    run_line(input);
  }
  return 0;
}

void run_line(char * input) {
    char temp[128];
    char * output = malloc(sizeof(char)*256);
    char ** args = malloc(sizeof(char*)*20);
    args = parse_args(input," ",count_occurence(input," ")+1);
    printf("%s",args[0]);


    if(count_occurence(input,"<") == 1) {
        char ** commands = parse_args(input,"<",count_occurence(input,"<")+1);
        commands[0] = remove_trailing(commands[0]," ");
        commands[1] = remove_trailing(commands[1]," ");
        char * filename = commands[1];
        if(count_occurence(commands[1],">") == 1) {

        }
        else {

            //strcpy(temp,commands[1]);
            //strcat(commands[0]," ");
            //strcat(commands[0],commands[1]);
            commands = parse_args(commands[0]," ",count_occurence(commands[0]," ")+1);
            //printf("%s %s %s %s\n",commands[0],commands[1],commands[2],commands[3]);
            args = commands;

            int f = open(filename,O_RDONLY);
            int save = dup(STDIN_FILENO);
            dup2(f,STDIN_FILENO);
            close(f);
            forkxec(args);
            dup2(save,0);
        }

    }//tr a-z A-Z < text.txt

     else if(count_occurence(input,">") == 1){
        char ** commands = parse_args(input,">",count_occurence(input,">")+1);
        commands[0] = remove_trailing(commands[0]," ");
        commands[1] = remove_trailing(commands[1]," ");
        FILE *cmd_output = popen(commands[0],"r");
        FILE *w = fopen(commands[1],"w");

        while (!feof(cmd_output)) {
            if (fgets(temp, 128, cmd_output) != NULL) {
                fprintf(w,"%s",temp);
            }
        }
        fclose(w);

    }

    else if(count_occurence(input,"|") == 1) {
      char ** pipe = parse_args(input,"|",count_occurence(input,"|")+1);
      pipe[0] = remove_trailing(pipe[0]," ");
      FILE *command = popen(pipe[0],"r");
      while (!feof(command)) {
        if (fgets(temp, 128, command) != NULL) {
          strcat(output,temp);
        }
      }
      pclose(command);

      args[1] = replace_char(output,"\n"," ");
      args[1][strlen(args[1])-1] = '\0';

      args[0] = remove_trailing(pipe[1]," ");
      strcat(args[0]," ");


      if(count_occurence(args[1], " ") > 0) {
          strcat(args[0],"-l ");
      }
      strcat(args[0],args[1]);
      //int s = count_occurence(args[0], " ");
      args = parse_args(args[0]," ",count_occurence(args[0], " ")+1);
      //args[s]

      forkxec(args);
      sleep(1);
    }
    else {
      int cmd_amt = count_occurence(input,";")+1;
      char ** command_list = parse_args(input,";",count_occurence(input,";")+1);
      int i = 0;
      //printf("\n%s",command_list[1]);


      for(int i = 0; i < cmd_amt; i++) {
        char * command = remove_trailing(command_list[i]," ");
        args = parse_args(command," ",count_occurence(command," ")+1);
        forkxec(args);
      }

    }

}

void forkxec(char ** args) {
    pid_t pid = fork();
        if(pid == 0) {
          //printf("\n%s %s %s %s %s",args[0],args[1],args[2],args[3],args[4]);
            if(strcmp(args[0],"exit") != 0 && strcmp(args[0],"cd") != 0) {
                execvp(args[0],args);
                //printf("%s",strerror(errno));
                wait(NULL);
            }
            exit(0);
        }
        else {
            if(strcmp(args[0],"cd") == 0) {
                if(!args[1]) {
                    chdir(getenv("HOME"));
                }
                else {
                    chdir(args[1]);
                }
            }
            wait(NULL);
        }

}

int main() {
  shell();
}
