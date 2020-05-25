#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
  int fd[2];
  int value;

  value = 0;
  
  pipe(fd);

  if (fork() == 0) { // child
    value = 50;
    printf("child writing %d to file descriptor #%d\n", value, fd[1]);
    write(fd[1], &value, sizeof(int));
    exit(0);
  } else { // parent
    printf("parent reading from file descriptor #%d\n", fd[0]);
    read(fd[0], &value, sizeof(int));
    printf("parent read value %d\n", value);
    wait(NULL);
  }

  return 0;
}
