from random import *
import sys

if len(sys.argv) != 2:
  print("usage: marbles [e for enumerate, r for random]")
  quit()

n_slots = 7
n_marbles = 6

slots = []
marbles = []

def check(marbles, key):
  if marbles == key:
    print(f"Correct solution {key} found for marbles {marbles}")
    quit()

def print_guess(marbles, key):
    print(f"Marbles: {marbles}")
    print(f"Key    : {key}")
    print()

def convert_to_base(base, n, m):
  arr = [0 for i in range(m)]
  j = m-1
  while n > 0:
    rem = n % base
    n = int(n / base)
    arr[j] = rem
    j -= 1
    arr[j] = n
  return arr

def random_marbles():
  while True:
    key = []
    for i in range(n_marbles):
      r = randint(0, n_slots)
      key.append(r)
    print(f"Marbles: {marbles}")
    print(f"Key    : {key}")
    print()
    check(marbles, key)

def enumerate_marbles():
  while True:
    for i in range(pow(n_marbles,n_slots)):
      key = convert_to_base(n_slots, i, n_marbles)
      print_guess(marbles, key)
      check(marbles, key)

for i in range(n_slots):
  slots.append(i)

for i in range(n_marbles):
  r = randint(0, n_slots)
  marbles.append(r)

print(f"Marbles: {marbles}")
input()

if sys.argv[1] == 'r':
  random_marbles()
else:
  enumerate_marbles()
