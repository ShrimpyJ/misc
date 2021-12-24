#ifndef ASTRING_H
#define ASTRING_H

#define BUFLEN 120

#include <stdlib.h>
#include <stdio.h>

typedef char* astring;

extern astring astring_get(const char *in)
{
  astring as = calloc(BUFLEN, sizeof(char));
  char *p;

  printf("%s", in);
  fgets(as, BUFLEN, stdin);

  // remove trailing newline
  p = &as[0];
  while(*p){
    if (*++p == '\n'){
      *p = '\0';
      break;
    }
  }

  return as;
}

#endif
