from sys import stdin
import matplotlib.pyplot as plt
import numpy as np
import operator

class Keyboard:
  def __init__(self, name, layout):
    self.name = name
    self.layout = layout
    self.total = 0
    self.heatmap = [[0 for x in range(len(self.layout[y]))] for y in range(len(self.layout))]

  def print_heatmap(self):
    h = self.heatmap
    for i in range(len(h)):
      for j in range(len(h[i])):
        print("%7d_%s" % (h[i][j], self.layout[i][j]), end = "")
      print()

alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m',
            'n', 'o','p','q','r','s','t','u','v','w','x','y','z',]

keyboards = []
def make_keyboard(name, layout, keyboards):
  kb = Keyboard(name, layout)
  keyboards.append(kb)

usi = [['q','w','e','r','t','y','u','i','o','p'],
       ['a','s','d','f','g','h','j','k','l',';'],
       ['z','x','c','v','b','n','m',',','.','/']]
make_keyboard("qwerty", usi, keyboards)

dvo = [['\'',',','.','p','y','f','g','c','r','l'],
       ['a','o','e','u','i','d','h','t','n','s'],
       [';','q','j','k','x','b','m','w','v','z']]
make_keyboard("dvorak", dvo, keyboards)

col = [['q','w','f','p','g','j','l','u','y',';'],
       ['a','r','s','t','d','h','n','e','i','o'],
       ['z','x','c','v','b','k','m',',','.','/']]
make_keyboard("colemak", col, keyboards)

wrk = [['q','d','r','w','b','j','f','u','p',';'],
       ['a','s','h','t','g','y','n','e','o','i'],
       ['z','x','m','c','v','k','l',',','.','/']]
make_keyboard("workman", wrk, keyboards)

qwe = [['q','w','e','r','t','z','u','i','o','p'],
       ['a','s','d','f','g','h','j','k','l',';'],
       ['y','x','c','v','b','n','m',',','.','/']]
make_keyboard("qwertz", qwe, keyboards)

aze = [['a','z','e','r','t','y','u','i','o','p'],
       ['q','s','d','f','g','h','j','k','l','m'],
       ['w','x','c','v','b','n',',','.','/','!']]
make_keyboard("azerty", aze, keyboards)


weights_1 = [[1,1,1,1,1,1,1,1,1,1],
             [0,0,0,0,1,1,0,0,0,0],
             [1,1,1,1,2,1,1,1,1,1]]
weights_2 = [[4,4,4,4,5,6,4,4,4,4],
             [0,0,0,0,4,4,0,0,0,0],
             [5,5,5,5,7,5,5,5,5,5]]
weights = weights_2

def get_weight(c, kb):
  arr = kb.layout
  for i in range(len(arr)):
    for j in range(len(arr[i])):
      if arr[i][j] == c:
        kb.heatmap[i][j] += 1
        return weights[i][j]
  return 0

for word in stdin:
  if word == '':
    break
  word = word.lower()
  for kb in keyboards:
    total = 0
    for c in word:
      weight = get_weight(c, kb)
      total += weight
    kb.total += total

keyboards.sort(key=operator.attrgetter('total'))

for kb in keyboards:
  print(f"Keyboard: {kb.name}")
  kb.print_heatmap()
  print(f"Total score: {kb.total}")
  for kb2 in keyboards:
    if kb == kb2:
      continue
    perc = abs(1 - kb.total / kb2.total) * 100
    print("%s is %.2f percent " % (kb.name, perc), end='')
    if kb.total >= kb2.total:
      print("less efficient ", end='')
    else:
      print("more efficient ", end='')
    print(f"than {kb2.name}")
  print()
  plt.imshow(kb.heatmap, cmap='viridis', interpolation='nearest')
  plt.title(kb.name)
  plt.savefig(kb.name + '.png')

def flatten(arr):
  ret = []
  for i in range(len(arr)):
    for j in range(len(arr[i])):
      ret.append(arr[i][j])
  return ret

kb = keyboards[0]
d = dict(zip(flatten(kb.layout), flatten(kb.heatmap)))
ds = dict(sorted(d.items(), key=lambda item: item[0]))
x = []
y = []
for item in ds:
  x.append(item)
  y.append(ds[item])

plt.clf()
plt.bar(x, y)
plt.title("Frequency of Characters")
plt.xlabel("Character")
plt.ylabel("Frequency")
plt.show()

x = []
y = []
ds = dict(sorted(d.items(), key=lambda item: item[1]))
for item in reversed(ds):
  x.append(item)
  y.append(ds[item])

plt.clf()
plt.bar(x, y)
plt.title("Frequency of Characters")
plt.xlabel("Character")
plt.ylabel("Frequency")
plt.show()
