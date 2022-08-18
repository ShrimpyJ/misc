#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define NAME "clash"

#define KEY_UP 72
#define KEY_DOWN 80

struct cmd{
  int argc;
  char **argv;
};

void cmd_free(struct cmd *cmd)
{
  int i;
  for (i = 0; i < cmd->argc; i++){
    free(cmd->argv[i]);
  }
  free(cmd->argv);
}

void print_path()
{
  char s[255];
  printf("%s", getcwd(s, 255));
}

void print_raw(void *start, size_t bytes, int align)
{
  unsigned char *p = (unsigned char *)start;
  int i;
  int index;
  int offset = (unsigned long)p % align;
  char ascii[align+1];
  void *v;

  if (bytes <= 0) return;

  /* Print info */
  printf("start: %08x\n", start);
  printf("  end: %08x", start+bytes-1);

  /* Initialize ASCII array */
  for (i = 0; i < align; i++) ascii[i] = '.';
  ascii[i+1] = '\0';

  /* If needed, print bytes preceding start for visual alignment */
  if (offset % align != 0){
    printf("\n%08x: ", start-offset);
    for (i = offset % align; i != 0; i--) printf("?? ");
    index = offset % align;
  }

  /* Print raw bytes aligned */
  for (p = (unsigned char *)start; p != start+bytes; p++){
    /* When full "line" of bytes are processed: */
    if ((unsigned long)p % align == 0){
      /* Print ASCII and reset ASCII array */
      if (p != start){
        printf(" ");
        for (i = 0; i < align; i++){
          printf("%c", ascii[i]);
          ascii[i] = '.';
        }
      }

      index = 0;

      /* Print next starting address */
      printf("\n%08x: ", p);
    }

    /* Print raw byte and set corresponding ASCII array value */
    printf("%02x ", *p);
    if ((unsigned char)*p >= ' ') ascii[index] = (unsigned char)*p;
    index++;
  }

  /* If needed, print bytes postceding end for visual alignemtn */
  offset = (unsigned long)p % align;
  if (offset % align != 0){
    for (i = 0; i < align - offset % align; i++){
      printf("?? ");
    }
  }

  /* Print last ASCII array */
  printf(" ");
  for (i = 0; i < align; i++) printf("%c", ascii[i]);
  printf("\n\n");
}

struct cmd *parse_input(char *input)
{
  struct cmd *out;
  char buf[255];
  int len = strlen(input);
  int argc = 0;
  int i;
  int count = 0;
  char c;
  int index;

  if (input[0] == '\n') return NULL;

  out = calloc(1, sizeof(struct cmd));
  for (i = 0; i < len; i++){
    while (input[i] == ' ') i++;

    if (input[i] == '\n') break;

    memset(buf, 0, 255);
    index = 0;
    while (input[i] != ' ' && input[i] != '\n'){
      memcpy(buf+index, input+i, 1);
      index++;
      i++;
    }

    argc++;
    if (argc-1 == 0) out->argv = calloc(1, sizeof(char *));
    else out->argv = realloc(out->argv, argc * sizeof(char *));

    out->argv[argc-1] = calloc(strlen(buf), sizeof(char));
    strncpy(out->argv[argc-1], buf, strlen(buf));
  }

  out->argc = argc;

  return out;
}

int main()
{
  pid_t child;
  char input[255];
  char pwd[255];

  while (1){
    print_path();
    printf("$ ");
    fgets(input, 255, stdin);

    if (strcmp("exit\n", input) == 0) break;
    if (strcmp("logout\n", input) == 0) break;

    struct cmd *cmd = parse_input(input);
    if (cmd == NULL) continue;

    if (strcmp(cmd->argv[0], "cd") == 0){
      if (chdir(cmd->argv[1]) != 0) fprintf(stderr, "%s: cd: %s: No such file or directory\n", NAME, cmd->argv[1]);
    }
    else if ((child = fork()) == 0){
      if (execvp(cmd->argv[0], cmd->argv) != 0) fprintf(stderr, "%s: %s: command not found\n", NAME, cmd->argv[0]);
      cmd_free(cmd);
      free(cmd);
      exit(0);
    }
    else{
      waitpid(child, NULL, 0);
    }

    cmd_free(cmd);
    free(cmd);
  }
}
