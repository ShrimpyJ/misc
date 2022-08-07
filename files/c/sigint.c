#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

volatile sig_atomic_t shutdown_flag = 1;

static void sigintHandler(int sig)
{
  printf("Caught SIGINT\n");
  shutdown_flag = 0;
}

static void sigtermHandler(int sig)
{
  printf("Caught SIGTERM\n");
//  shutdown_flag = 0;
}

int main()
{
  int i = 0;
  FILE *f = fopen("i.txt", "w");

  if (signal(SIGINT, sigintHandler) == SIG_ERR){
    perror("signal SIGINT");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGTERM, sigtermHandler) == SIG_ERR){
    perror("signal SIGTERM");
    exit(EXIT_FAILURE);
  }

  while (shutdown_flag){
    printf("%d\n", i);
    sleep(3);
    i++;
  }

  printf("Writing i's value to file...\n");
  char str[10];
  sprintf(str, "%d\n", i);
  fwrite(str, 1, strlen(str), f);
}
