from random import *
import sys
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) != 3:
  print("usage: acgt inner_iterations outer_iterations")
  sys.exit(0)

iterations = int(sys.argv[1])
outer = int(sys.argv[2])

def loop():
  ls = []
  rs = []
  AT = 0
  CG = 0
  
  bases = ["A", "C", "T", "G"]
  A_bound = 15
  T_bound = A_bound*2
  C_bound = int(100-(100-T_bound)/2)
  G_bound = 100
  outlier_per = 0.15
  outlier = A_bound*2 + (A_bound*2)*outlier_per
  if (A_bound >= 50):
    print("Error: A_bound cannot be > 49")
    quit()
  
  for i in range(iterations):
    r = randint(1, 100)
    if r <= A_bound:
      r = 0
    elif r > A_bound and r <= T_bound:
      r = 2
    elif r > T_bound and r <= C_bound:
      r = 1
    elif r > C_bound and r <= G_bound:
      r = 3
    else:
      print("Error: invalid r value {}" % r)
    ls.append(bases[r])
    rs.append(bases[(r+2)%4])
  
  for i in range(len(ls)):
    if ls[i] == "A" or rs[i] == "A":
      AT += 1
    else:
      CG += 1
  
  AT_f = AT / iterations * 100
  CG_f = CG / iterations * 100
  if AT_f > outlier:
    print("A/T: %.2f percent\nC/G: %.2f percent\n" % (AT_f, CG_f))

  return AT_f
 
data = []
for i in range(outer):
  data.append(loop())

data = np.random.randn(10000, 3)
n, bins, patches = plt.hist(data, bins=50, density=True)
plt.show()
