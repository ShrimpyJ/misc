import threading as thread
import time
import turtle

f_24 = 1000 / 24 / 1000
f_60 = 1000 / 60 / 1000
f_120 = 1000 / 120 / 1000

size = 80
step = 2
delay = 1000 / 60 / 1000
ydist = 20

pos = [0]

class Screen:
  def __init__(self, index):
    self.index = index
    self.xstart = 0
    self.ystart = self.index * -ydist
    self.t = turtle.Turtle()
    self.t.goto(self.xstart, self.ystart)
    self.t.clear()

  def print_turtle(self, pos):
    if pos[0] > size:
      self.t.goto(self.xstart, self.ystart)
    else:
      self.t.goto(self.xstart + step*pos[0], self.ystart)

def update_pos(delay, pos):
  while True:
    if pos[0] > size:
      pos[0] = 0
    else:
       pos[0] += 1
    time.sleep(delay)

s1 = Screen(0)
s2 = Screen(1)

t1 = thread.Thread(target=update_pos, args=(delay,pos))
t1.start()

while True:
  s1.print_turtle(pos)
  s2.print_turtle(pos)
  time.sleep(f_120)
