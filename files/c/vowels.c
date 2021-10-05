#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  char c;
  struct node *next, *prev;
} Node;

Node *nodify_string(char *s)
{
  int i;
  int len;
  Node *ret;
  Node *n;

  ret = malloc(sizeof(Node *));
  ret->c = s[0];

  n = malloc(sizeof(Node *));
  ret->next = n;
  n->prev = ret;

  len = strlen(s);
  for (i = 1; i < len; i++){
    Node *next, *prev;
    next = malloc(sizeof(Node *));
    n->c = s[i];
    prev = n;
    n->next = next;
    n = next;
    n->prev = prev;
  }

  return ret;
}

void ll_reverse(Node *n)
{
  while (n){
    printf("%c", n->c);
    n = n->prev;
  }
}

void ll_traverse(Node *n)
{
  while (n->next){
    printf("%c", n->c);
    n = n->next;
  }
}

Node *ll_remove(Node *n)
{
  if (n->prev) n->prev->next = n->next;
  n->next->prev = n->prev;

  return n->next;
}

Node *remove_vowels(Node *n, int len)
{
  Node *ret;

  ret = n;

  while (n->next){
    if (n->c == 'a' || n->c == 'e' || n->c == 'i' || n->c == 'o' || n->c == 'u' ||
        n->c == 'A' || n->c == 'E' || n->c == 'I' || n->c == 'O' || n->c == 'U')
    {
      n = ll_remove(n);
    }
    else n = n->next;
  }

  return ret;
}

void vowel_replace(char *s)
{
  int i;

  for (i = 0; i < strlen(s); i++){
    if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||
        s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
    {
      s[i] = '-';
    }
  }
}

int main(int argc, char** argv)
{
  char s[] = "We need your help to retrieve all of the vowels! Will you aid us?";
  Node *start;
  Node *new;

//  start = nodify_string(s);
//  new = remove_vowels(start, strlen(s));
//  ll_traverse(new);

  vowel_replace(s);
  printf("%s\n", s);

  return 0;
}
