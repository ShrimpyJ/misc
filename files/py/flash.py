import threading as thread
import time

lock = thread.Lock()
f_24 = 1000 / 24 / 1000
f_30 = 1000 / 30 / 1000
f_48 = 1000 / 48 / 1000
f_60 = 1000 / 60 / 1000
f_120 = 1000 / 120 / 1000

s2pos = 2

def print_c(c, pos, delay):
  while True:
    for i in range(pos):
      print(" ", end=' ')
    print(c)
    time.sleep(delay)

try:
  t1 = thread.Thread(target=print_c, args=(" ", 0, .1))
  t2 = thread.Thread(target=print_c, args=("h", 0, f_24))
  t3 = thread.Thread(target=print_c, args=("h", s2pos, f_60))
except:
  print("Error: unable to start thread")

t1.start()
t2.start()
t3.start()

while 1:
  pass
