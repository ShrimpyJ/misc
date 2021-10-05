Simple API for a trie of strings.

Example usage:
struct trie T;
T = trie_create();
trie_insert(T, "penguin");
trie_insert(T, "dolphin");
struct node *n = trie_find(T, "dolphin");
OR
if (trie_find(T, "dolphin")){
  /* take some action */
}
else{
  /* print some error */
}
trie_destroy(T);

Compile by linking trie.c, main.c is just for reading a file delimited by newlines.
