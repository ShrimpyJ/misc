from random import *
import sys
import numpy as np
import threading

# A length=4 maze has the following indexes (8 is victory)
#  8
# 76
# 54
# 32
# 10

class Shared:
  def __init__(self, length):
    self.length = length

class Guest:
  def __init__(self, id, pos, moves, facing, shared):
    self.id = id
    self.pos = pos
    self.moves = moves
    self.facing = facing
    self.shared = shared

  def Start(self):
    while self.pos != length*2:
      self.Move()
    print("Guest %d has finished in %d moves" % (self.id, self.moves))

  def Move(self):
    viable = []
    if self.facing == 0:   # Up
      viable.append(0)
      viable.append(3)
    elif self.facing == 1: # Right
      if self.pos != 0:
        viable.append(2)
      viable.append(0)
    elif self.facing == 2: # Down
      if self.pos != 0:
        viable.append(2)
      viable.append(3)
    elif self.facing == 3: # Left
      viable.append(1)
    
    r = randint(0, 3)
    while not is_viable(r, viable):
      r = (r + 1) % 4

    self.moves += 1
    self.Update(r)

  def Update(self, r):
    self.facing = r
    if r == 0:    # Up
      self.pos += 2
    elif r == 1:  # Right
      self.pos -= 1
    elif r == 2:  # Down
      self.pos -= 2
    elif r == 3:  # Left
      self.pos += 1

def is_viable(r, viable):
  for v in viable:
    if v == r:
      return True
  return False

if len(sys.argv) != 4:
  print("usage: maze.py length num_guests concurrency(y/n)")
  exit()

length = int(sys.argv[1])
nguests = int(sys.argv[2])
concurrency = 0
if sys.argv[3] == "y":
  concurrency = 1
elif sys.argv[3] == "n":
  concurrency = 0
else:
  print("error: invalid concurrency option '%s' (should be y/n)" % sys.argv[3])
  exit()

s = Shared(length)

#threads = []
for i in range(nguests):
  g = Guest(i, 0, 0, 0, s)
  g.Start()
#  t = threading.Thread(target=g.Start(), args=())
#  threads.append(t)
#
#for i, t in enumerate(threads):
#  print("Thread %s starting" % i)
#  t.start()
#
#for i, t in enumerate(threads):
#  print("Thread %d joining" % i)
#  t.join()
