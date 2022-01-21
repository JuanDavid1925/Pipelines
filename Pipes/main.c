
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


#define READ  0
#define WRITE 1

int main() 
{
  pid_t pid;
  int fd[2];
  char buf[10];
  int numRandom;
  srand (getpid());
  numRandom = rand() % 1000 + 1;

  if (pipe(fd) == -1) 
  {
	  perror("Creating pipe");
	  exit(EXIT_FAILURE);
  }

  switch(pid = fork()) 
  {
    case 0:
	  // The child process will execute wc.
	  // Close the pipe write descriptor.
	  close(fd[WRITE]);
    read(fd[0], buf, 4);
    if(atoi(buf) <= 500)
    {
       printf("El numero generado es menor o igual a 500, se genero el numero:  %d \n",atoi(buf));
    }
    else
    {
      printf("El numero generado es mayor o igual a 500, se genero el numero:  %d \n ",atoi(buf));
    }
    exit(0);
	  

    case -1:
	  perror("fork() failed)");
	  exit(EXIT_FAILURE);

    default:
	  // The parent process will execute ls.
	  // Close the pipe read descriptor.
	  close(fd[READ]);
    sprintf(buf, "%d", numRandom);
    write(fd[1],buf,4);
    close(fd[1]);
	  
  }
}

