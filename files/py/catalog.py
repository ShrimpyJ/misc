from random import *

class Thread:
    self.mac 
  def __init__(self):
    self.title = ""
    self.posts = 0
    self.replies = []

  def print(self):
    print("Thread: " + self.title)
    print("Posts: " + str(self.posts))
    for reply in self.replies:
      print(reply)

  def add_reply(self, reply):
    self.replies.append(reply)
    self.posts += 1

def read_file(f):
  f = open(f, 'r')
  lines = f.read().splitlines()
  f.close()
  return lines

def create_threads(lines, num):
  threads = []
  for i in range(num):
    t = Thread()
    r = randint(1, len(lines))
    t.title = lines[r]
    threads.append(t)
  return threads

def print_threads(threads):
  for t in threads:
    t.print()
    print()

def form_reply(lines):
  words = randint(1, 8)
  reply = ""
  for i in range(words):
    r = randint(1, len(lines))
    reply += lines[r]
    reply += " "
  return reply

# Read file into array of lines
lines = read_file("/home/pete/words.txt")

# Create array of threads and give each a random title
threads = create_threads(lines, 5000)

for i in range(50):
  n = randint(0, len(threads)-1)
  t = threads[n]
  t.add_reply(form_reply(lines))
  threads.insert(0, threads.pop(n))
  print_threads(threads)
  print("###")
