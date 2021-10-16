import random
import string
import sys

multiplier = 2
max_words = 20

def print_grid(grid):
  l = len(grid)
  for i in range(3):
    print(" ", end="")
  for i in range(l):
    print("%2d" % (i%10), end="")
  print()
  for i in range(3):
    print(" ", end="")
  for i in range(l*2):
    print("-", end="")
  print()

  for i in range(l):
    print("%2d" % i, end="| ")
    for j in range(l):
      print(grid[i][j] + " ", end="")
    print()

def check_fits(word, direction, row, col, maxlen):
  l = len(word)
  if direction == 0:    # right
    if col + l > maxlen:
      return -1
    return 0
  elif direction == 1:  # down
    if row + l > maxlen:
      return -1
    return 1
  elif direction == 2:  # left
    if col+1 - l < 0:
      return -1
    return 2
  elif direction == 3:  # up
    if row+1 - l < 0:
      return -1
    return 3

def insert_word(grid, word):
  l = len(grid)
  row = random.randint(0, l-1)
  col = random.randint(0, l-1)
  direction = random.randint(0, 3)
  while check_fits(word, direction, row, col, l) == -1:
    row = random.randint(0, l-1)
    col = random.randint(0, l-1)
    direction = random.randint(0, 3)
  d = check_fits(word, direction, row, col, l)

  if direction == 0:    # right
    for i in range(len(word)):
      grid[row][col+i] = word[i]
  elif direction == 1:  # down
    for i in range(len(word)):
      grid[row+i][col] = word[i]
  elif direction == 2:  # left
    for i in range(len(word)):
      grid[row][col-i] = word[i]
  elif direction == 3:  # up
    for i in range(len(word)):
      grid[row-i][col] = word[i]

def check_right(grid, word, row, col):
  if len(word) == 0:
    return 1

  if col > len(grid)-1:
    return 0

  if grid[row][col] == word[0]:
    return check_right(grid, word[1:], row, col+1)
  return 0

def check_left(grid, word, row, col):
  if len(word) == 0:
    return 1

  if col < 0:
    return 0

  if grid[row][col] == word[0]:
    return check_left(grid, word[1:], row, col-1)
  return 0

def check_up(grid, word, row, col):
  if len(word) == 0:
    return 1

  if row < 0:
    return 0

  if grid[row][col] == word[0]:
    return check_up(grid, word[1:], row-1, col)
  return 0

def check_down(grid, word, row, col):
  if len(word) == 0:
    return 1

  if row > len(grid)-1:
    return 0

  if grid[row][col] == word[0]:
    return check_down(grid, word[1:], row+1, col)
  return 0

def get_pos(grid, c):
  l = len(grid)
  pos_arr = []
  for i in range(l):
    for j in range(l):
      if grid[i][j] == c:
        pos_arr.append([i, j])
  return pos_arr

def find_word(grid, word):
  pos_arr = get_pos(grid, word[0])
  for pos in pos_arr:
    if check_right(grid, word, pos[0], pos[1]):
      print("FOUND", word, "GOING RIGHT AT", pos[0], pos[1])
      return pos
    elif check_left(grid, word, pos[0], pos[1]):
      print("FOUND", word, "GOING LEFT AT", pos[0], pos[1])
      return pos
    elif check_up(grid, word, pos[0], pos[1]):
      print("FOUND", word, "GOING UP AT", pos[0], pos[1])
      return pos
    elif check_down(grid, word, pos[0], pos[1]):
      print("FOUND", word, "GOING DOWN AT", pos[0], pos[1])
      return pos
  print("COULD NOT FIND", word, "IN GRID")
  return -1

words = []

for line in sys.stdin:
  if line == '':
    break
  if len(words) > max_words:
    break
  words.append(line)

# convert words to uppercase and find longest word's length
maxlen = 0
for i in range(len(words)):
  words[i] = words[i].rstrip()
  words[i] = words[i].upper()
  if len(words[i]) > maxlen:
    maxlen = len(words[i])

l = maxlen*multiplier

# initialize grid with random characters
grid = []
for i in range(l):
  grid.append([])
  for j in range(l):
    grid[i].append(random.choice(string.ascii_letters).upper())

for word in words:
  insert_word(grid, word)

print_grid(grid)

for word in words:
  find_word(grid, word)
