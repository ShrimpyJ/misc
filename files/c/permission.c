#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define EXECUTE   001
#define WRITE     002
#define READ      004

#define BUFLEN    100

#define ADDUSER     0
#define SETPERM     1
#define ADDPERM     2
const char *COMMANDS[] = {"adduser", "setperm", "addperm"};
const int NUM_COMMANDS = 3;

typedef struct user {
  char name[80];
  uint16_t permissions;
} User;

typedef struct cmd {
  char *buf;
  char **args;
  int nargs;
  int command;
} Cmd;

void bool_exception()
{
  fprintf(stderr, "error: invalid bool\n");
  exit(1);
}

uint16_t set_permissions(User *u, int read, int write, int execute)
{
  if (read < 0 || read > 1) bool_exception();
  if (write < 0 || write > 1) bool_exception();
  if (execute < 0 || execute > 1) bool_exception();
  u->permissions = (read << 2) | (write << 1) | execute;
}

uint16_t get_permissions(User *u)
{
  if (u->permissions & 1) printf("user has execute permissions\n");
  if (u->permissions & 2) printf("user has write permissions\n");
  if (u->permissions & 4) printf("user has read permissions\n");
}

Cmd *parse(char *buf)
{
  Cmd *cmd = calloc(1, sizeof(Cmd));
  cmd->buf = calloc(strlen(buf)+1, sizeof(char));
  strncpy(cmd->buf, buf, strlen(buf));
  int nargs = 1;
  int i, j;
  char *p = &buf[0];
  if (*buf == '\n' || *buf == '\0') return NULL;

  while (*p != '\n' && *p != '\0'){
    if (*p == ' ' || *p == '\t'){
      nargs++;
      while (*p == ' ' || *p == '\t') p++;
    }
    p++;
  }

  cmd->nargs = nargs;
  cmd->args = calloc(nargs, sizeof(char *));
  for (i = 0; i < nargs; i++) cmd->args[i] = calloc(BUFLEN, sizeof(char));

  p = &buf[0];
  i = j = 0;
  while (*p != '\n' && *p != '\0'){
    if (*p == ' ' || *p == '\t'){
      while (*p == ' ' || *p == '\t') p++;
      i++;
      j = 0;
    }
    cmd->args[i][j] = *p;
    j++;
    p++;
  }

  return cmd;
}

int parse_args(Cmd *cmd)
{
  int i;

  cmd->command = -1;
  for (i = 0; i < NUM_COMMANDS; i++){
    if (strcmp(cmd->args[0], COMMANDS[i]) == 0){
      cmd->command = i;
      break;
    }
  }

  if (cmd->command < 0) return -1;



  return cmd->command;
}

int main()
{
  char *buf;
  int action;

  buf = calloc(BUFLEN, sizeof(char));
  action = 0;
  while(1){
    memset(buf, 0, BUFLEN);
    fgets(buf, BUFLEN, stdin);
    Cmd *cmd = parse(buf);
    if (!cmd) continue;
    printf("%s", cmd->buf);
    if (parse_args(cmd) < 0) continue;
  }
}
