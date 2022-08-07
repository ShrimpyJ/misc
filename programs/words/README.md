# Writeup
We want to find n words of x length with NO common letters shared between them.

Ex. n=4 words x=3 letters each:
  ace, bin, dog, fry

This is valid since no letter appears twice in the concatenation of words:
  acebindogfry

Sorting the concatenated word alphabetically further reveals this:
  abcdefginory

For n=5 and x=5, 25 out of 26 letters would need to be used.
With a large word list, this can be brute forced.

To compare strings faster, assign each letter in the alphabet to one bit of a 32-bit integer.
There will be 6 unused bits.

Here, a is the least significant bit:
00000000 00000000 00000000 00000000
      zy xwvutsrq ponmlkji hgfedcba

Turn the bits on when a letter appears in that word.
This only works for words without repeating letters, which is fine for our purpose.

Example: ace
00000000 00000000 00000000 00010101 = 21 in decimal
      zy xwvutsrq ponmlkji hgfedcba

Example: bar
00000000 00000010 00000000 00000011 = 131075 in decimal
      zy xwvutsrq ponmlkji hgfedcba

To determine if two words share a common letter, AND the numbers together:
  00000000 00000000 00000000 00010101 ace
& 00000000 00000010 00000000 00000011 bar
  -----------------------------------
  00000000 00000000 00000000 00000001

Since they share an 'a', ace AND bar equals 1.
Any words that do NOT share a common letter will equal 0.

Example:
  00000000 00000000 00000000 00010101 ace
& 00000000 00000000 00100001 00000010 bin
  -----------------------------------
  00000000 00000000 00000000 00000000

This already completes the algorithm for n=2 words x=3 letters
But what if n=4 words?

To demonstrate, let's take a sample list of 3-letter words to work with:
ace
bar
bye
bin
car
cat
dog
dim
fry

To find n=4 words with no matching letters, start with the first word.

ace

Next, AND it with every word in the list until it yields a 0.

ace & bar != 0, next word
ace & bye != 0, next word
ace & bin == 0

This gives n=2. To continue, concatenate 'ace' with 'bin' by performing an OR with their numbers:
  00000000 00000000 00000000 00010101 ace
| 00000000 00000000 00100001 00000010 bin
  -----------------------------------
  00000000 00000000 00100001 00010111 acebin

This new word, 'acebin' if you will, can now be used in place of the original word 'ace'.
Continue down the list with 'acebin', AND'ing it with each word until it yields a 0.

acebin & car != 0, next word
acebin & cat != 0, next word
acebin & dog == 0

This gives n=3, which is close. To continue, repeat the OR process with 'acebin' and 'dog':
  00000000 00000000 00100001 00010111 acebin
| 00000000 00000000 01000000 01001000 dog
  -----------------------------------
  00000000 00000000 01100001 01011111 acebindog

Continue down the list with 'acebindog', AND'int as usual until 0 is found.

acebindog & dim != 0, next word
acebindog & fry == 0

This gives n=4, which satisfies the condition.
This algorithm is best done recursively, though it could work iteratively as well.

As for n=5 and x=5, the wordlist I used found 1673 unique combinations, though most of the words such as 'uayeb' are not considered proper English.
