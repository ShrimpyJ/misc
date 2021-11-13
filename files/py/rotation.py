import sys
import numpy as np
import math

def rotate(a, b, t):
  rot = [[0,0,0], [0,0,0], [0,0,0]]
  a = np.deg2rad(a)
  b = np.deg2rad(b)
  t = np.deg2rad(t)

  rot[0][0] = np.cos(t) * np.cos(b)
  rot[0][1] = -np.sin(t) * np.cos(a) + np.cos(t) * np.sin(b) * np.sin(a)
  rot[0][2] = np.sin(t) * np.sin(a) + np.cos(t) * np.sin(b) * np.cos(a)

  rot[1][0] = np.sin(t) * np.cos(b)
  rot[1][1] = np.cos(t) * np.cos(a) + np.sin(t) * np.sin(b) * np.sin(a)
  rot[1][2] = -np.cos(t) * np.sin(a) + np.sin(t) * np.sin(b) * np.cos(a)

  rot[2][0] = -np.sin(b)
  rot[2][1] = np.cos(b) * np.sin(a)
  rot[2][2] = np.cos(b) * np.cos(a)

  for i in range(len(rot)):
    for j in range(len(rot[i])):
      if np.absolute(rot[i][j]) < 0.001:
        rot[i][j] = 0

  return rot

if len(sys.argv) != 4:
  print("usage: rotation.py z_rotation y_rotation x_rotation")
  quit()

a = int(sys.argv[3])
b = int(sys.argv[2])
t = int(sys.argv[1])

rot = rotate(a,b,t)
print(rot)
