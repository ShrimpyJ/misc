from sys import stdin
import matplotlib.pyplot as plt
import numpy as np
import operator

class Keyboard:
  def __init__(self, name, layout):
    self.name = name
    self.layout = layout
    self.total = 0

keyboards = []
def make_keyboard(name, layout, keyboards):
  kb = Keyboard(name, layout)
  keyboards.append(kb)

usi = [['q','w','e','r','t','y','u','i','o','p'],
       ['a','s','d','f','g','h','j','k','l',';'],
       ['z','x','c','v','b','n','m',',','.','/']]
make_keyboard("qwerty", usi, keyboards)

col = [['q','w','f','p','g','j','l','u','y',';'],
       ['a','r','s','t','d','h','n','e','i','o'],
       ['z','x','c','v','b','k','m',',','.','/']]
make_keyboard("colemak", col, keyboards)

def find_key(kb, c):
  for i in range(len(kb)):
    for j in range(len(kb[i])):
      if kb[i][j] == c:
        return i, j
  return -1, -1

s = input()
for c in s:
  i, j = find_key(usi, c)
  if i == -1 and j == -1:
    t = c
  else:
    t = col[i][j]
  print(t, end='')
print()
