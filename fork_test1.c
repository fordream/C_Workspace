#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main( ){

  pid_t pid;

  pid=fork();

  if( pid<0){

    printf( "Fork failed");
  }
  else if( pid==0)
    execlp("/bin/ls", "ls -la", NULL);
  else{

    wait( NULL);
    printf( "Child Complete");
    exit( 0);
  }
}



















