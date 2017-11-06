#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


#define SAMSH_BUFFER_SIZE 1024
#define SAMSH_TOK_BUFSIZE 64

//builtin functions in the shell
int samsh_cd(char** args);
int samsh_help(char** args);
int samsh_exit(char**args);


/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &samsh_cd,
  &samsh_help,
  &samsh_exit
};

int samsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int samsh_cd(char ** args){

  if(args[1]== NULL){
    fprintf(stderr, "samsh: expected argument to \"cd\"\n" );
  }
  else{
    if (chdir(args[1])!= 0) {
      /* code */
      perror("samsh");
    }
  }
  return 1;
}

int samsh_help(char **args)
{
  int i;
  printf("Welcome to samsh, a shell built by Samagra Sharma ...\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i <samsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int samsh_exit(char **args)
{
  return 0;
}

int samsh_launch(char** args){
  pid_t pid,wpid;
  pid = fork();
  int status;
  if (pid==0) {
    /* code */
    /*This is the child process*/
    if (execvp(args[0],args) == -1 ) {
      /* code */
      perror("samsh");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid<0) {
    /* code */
    perror("samsh");
  }
  else{
    //parent process
    do {
      /* code */
      wpid = waitpid(pid,&status,WUNTRACED);
    } while(!WIFEXITED(status)&&!WIFSIGNALED(status));
  }
  return 1;
}

int samsh_execute(char ** args){

  if(args[0]==NULL){
    //do nothing
    return 1;
  }


  for (int i = 0; i < samsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
       return (*builtin_func[i])(args);
    }


  }
 return samsh_launch(args);

}

char * samsh_read(){
  int bufsize = SAMSH_BUFFER_SIZE;
  int character;
  char * buffer = malloc(sizeof(char)*SAMSH_BUFFER_SIZE);
  int position = 0;

  if (!buffer){
    fprintf(stderr, "%s\n","samsh: allocation error" );
    exit(EXIT_FAILURE);
  }


  while (1){
    character = getchar();

    if (character ==EOF || character=='\n'){
      buffer[position] = '\0';
      return buffer;
    }
    else{
      buffer[position] = character;
    }
    position ++;

    if(position>bufsize){
      bufsize+= SAMSH_BUFFER_SIZE;
      buffer = realloc(buffer,bufsize);
      if (!buffer){
        fprintf(stderr, "%s\n","samsh: allocation error" );
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define SAMSH_TOK_DLM " \n\t\a\r"

char ** samsh_parse(char*line){
  int bufsize = SAMSH_TOK_BUFSIZE, position =0;
  char * token;
  char ** tokens = malloc (sizeof(char*)*bufsize) ;
  if (!tokens){
    fprintf(stderr, "%s\n","samsh: allocation error" );
    exit(EXIT_FAILURE);
  }

  token = strtok(line,SAMSH_TOK_DLM);
  while(token!= NULL){
    tokens[position] = token;
    position ++;
    if(position>bufsize){
      bufsize+=bufsize;
      tokens = realloc(tokens,bufsize);
      if (!tokens){
        fprintf(stderr, "%s\n","samsh: allocation error" );
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL,SAMSH_TOK_DLM);
  }
  tokens[position] = NULL;
  return tokens;
}

void samsh_loop(void){
  char *line;
  char **args;
  int status;

  do {
    /* code */
    printf("%s","> " );
    line = samsh_read(); //reading from the command line
    args = samsh_parse(line);
    status = samsh_execute(args);

    //freeing the memory
    free(line);
    free(args);


  } while(status);
}

int main(int argc, char **argv) {
  /* code */
  //load config files if any

  //run the command loop
  samsh_loop();

  //Perform any shutdown cleanup

  return EXIT_SUCCESS;
}
