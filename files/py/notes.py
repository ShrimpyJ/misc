import math
import matplotlib.pyplot as plt

def round_school(x):
  i, f = divmod(x, 1)
  return int(i + ((f >= 0.5) if (x > 0) else (f > 0.5)))

def aliased_freq(fs, f):
  return abs(f - fs * round_school(f/fs))

def combine_responses(r1, r2):
  res = []
  for i in range(len(r1)):
    res.append(r1[i] + r2[i])
  return res

def f(x):
  return math.sin(x)

def get_hk(h):
  di = {}
  for key in h:
    if key*-1 in h:
      h[key] = h[key*-1]
    else:
      di[key*-1] = h[key]
      h[key] = 0
  h.update(di)

  hk = []
  for key in h:
    hk.append([key,h[key]])
  hk = sorted(hk, key=lambda x: x[0])
  while hk[0][1] == 0:
    hk.pop(0)
  while hk[len(hk)-1][1] == 0:
    hk.pop(len(hk)-1)
  return hk

def nl(arr):
  x = []
  y = []
  for i in arr:
    x.append(i[0])
    y.append(i[1])
  return x, y

def conv(x, h):
  lx = len(x)
  lh = len(h)
  hk = get_hk(h)

  hkp = nl(hk)
  xp = nl(x)
  plt.bar(hkp[0], hkp[1])
  plt.bar(xp[0], xp[1])
  plt.show()

def AM(f0, A, M, f1, o, t_array):
  f_1a = []
  f_2a = []
  for t in t_array:
    c = A * math.sin(2*3.14159*(f0*t+o))
    m = M * math.cos((2*3.14159)*(f1*(t+1)+o))
    f_1 = m * c
    f_2 = (1 + m) * c + 5
    f_1a.append(f_1)
    f_2a.append(f_2)
  return f_1a, f_2a

step = 0.001
start = -5
end = 5
i = start
t = []
while i < end:
  t.append(i)
  i += step
f = AM(0.1,1,1,4,0.5,t)
plt.plot(f[0])
plt.plot(f[1])
plt.show()

x = [[0,1], [1,0], [2, -1]]
h = {-1: 1, 0: 2, 1:-1, 2:-1}
