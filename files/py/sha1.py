from random import *
import sys

MOD = 2 ** 32

def shift_left(n, shifts):
  for i in range(shifts):
    n *= 2
  return n

def get_F(B, C, D):
 #n = randint(1, 58)*B**randint(2, 64) + randint(3, 5)*C**randint(2, 64) + D**randint(2,64)
 n = B**3 - C**4 - D**5
 print(n)
 return n

def sha1(n):
  a = n & 0xFFFFFFFF00000000000000000000000000000000
  b = n & 0x00000000FFFFFFFF000000000000000000000000
  c = n & 0x0000000000000000FFFFFFFF0000000000000000
  d = n & 0x000000000000000000000000FFFFFFFF00000000
  e = n & 0x00000000000000000000000000000000FFFFFFFF

  f = get_F(b, c, d)

  adder_1 = (e + f) % MOD
  adder_2 = (adder_1 + shift_left(a, 5)) % MOD
  adder_3 = (adder_2) % MOD
  adder_4 = (adder_3) % MOD

  A = adder_4
  B = a
  C = shift_left(b, 30)
  D = c
  E = d

  h = shift_left(A, 128) | shift_left(B, 96) | shift_left(C, 64) | shift_left(D, 32) | E

  return h

n = 3936939692696939696239636962
print("Before: " + str(n))
print("After : " + str(sha1(n)))
