import threading as thread
import time
import turtle

lock = thread.Lock()
f_24 = 1000 / 24 / 1000
f_60 = 1000 / 60 / 1000
f_120 = 1000 / 120 / 1000

size = 200
step = 20
delay = 1000 / 60 / 1000
ydist = 20

POS = 0

class Screen:
  def __init__(self, pos, c, index):
    self.pos = pos
    self.c = c
    self.index = index
    self.t = turtle.Turtle()
    self.xstart = -200
    self.ystart = index * - ydist
    self.t.goto(self.xstart, self.ystart)
    self.t.clear()

  def print_turtle(self):
    if self.pos > size:
      self.t.goto(self.xstart, self.ystart)
    else:
      self.t.goto(self.xstart + step*self.pos, self.ystart)

  def print(self):
    for i in range(self.pos):
      print(" ", end=' ')
    print(self.c)

  def move(self):
    if self.pos > size:
      self.pos = 0
    else:
      self.pos += 1

def update_scr(s, d):
  while True:
#    s.print()
    time.sleep(d)

def update_pos(s, d):
  while True:
    s.move()
    time.sleep(d)

s1 = Screen(0, "h", 0)
s2 = Screen(0, "x", 1)

try:
  t1 = thread.Thread(target=update_pos, args=(s1,delay))
  t2 = thread.Thread(target=update_scr, args=(s1,f_24))

  t3 = thread.Thread(target=update_pos, args=(s2,delay))
  t4 = thread.Thread(target=update_scr, args=(s2,f_60))
except:
  print("Error: unable to start thread")

t1.start()
t2.start()
t3.start()
t4.start()

while 1:
  s1.pos = s2.pos
  s1.print_turtle()
  time.sleep(f_60)
  pass
