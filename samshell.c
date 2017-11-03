
#define SAMSH_BUFFER_SIZE 1024

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
    c = getChar();

    if (c==EOF || c=='\n'){
      buffer[position] = '\0';
      return buffer;
    }
    else{
      buffer[position] = c;
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

char ** samsh_parse(char*line){
  
}

void samsh_loop(){
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
