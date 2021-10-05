from random import *
import sys

class Layer:
  def __init__(self, ninputs):
    self.data = []
    for i in range(ninputs):
      self.data.append(0.0)

def genrand(n):
  arr = []
  for i in range(n):
    arr.append(randint(1,100) * .01)
  return arr

if len(sys.argv) != 3:
  print("usage: net.py num_inputs num_layers")
  quit()
    
ninputs = int(sys.argv[1])
nlayers = int(sys.argv[2])

layers = []
for i in range(nlayers):
  l = Layer(ninputs)
  layers.append(l)

begin = layers[0]
end = layers[nlayers-1]

x = genrand(ninputs)
for i in range(ninputs):
  begin.data[i] = x[i]

for l in layers:
  print(l.data)
