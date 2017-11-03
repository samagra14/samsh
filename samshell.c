
#define SAMSH_BUFFER_SIZE 1024
#define SAMSH_TOK_BUFSIZE 64

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
    character = getChar();

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

#define SAMSH_TOK_DLM ' \n\t\a\r'

char ** samsh_parse(char*line){
  int bufsize = SAMSH_TOK_BUFSIZE, position =0;
  char * token;
  char ** tokens = malloc (sizeof*(char*)*bufsize) ;
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
    printf("%s\n","> " );
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
