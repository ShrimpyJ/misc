import threading as thread

threads = []

class Edge:
  def __init__(self, f, t, inputs):
    self.f = f
    self.t = t
    self.inputs = inputs

class State:
  def __init__(self, name):
    self.name = name
    self.edges = []

def read_state(state, string, i, substring, F):
  if i == len(string):
    return

  print(f"state: {state.name}")

  if state == F:
    print(f"accept state {F.name} reached")
    print(f"substring {substring} at index {i - len(substring)}")
    quit()

  for edge in state.edges:
    for ei in edge.inputs:
      if ei == string[i]:
        if edge.t != edge.f:
          substring += ei
        t = thread.Thread(target=read_state, args=(edge.t, string, i+1, substring, F))
        threads.append(t)
        t.start()
      if ei == 'epsilon':
        t = thread.Thread(target=read_state, args=(edge.t, string, i, substring, F))
        threads.append(t)
        t.start()

q1 = State('q1')
q2 = State('q2')
q3 = State('q3')
q4 = State('q4')

sigma = ['0', '1']
q0 = q1
F = q4

string = '0011001010'
substrings = ['11', '101']

q1.edges.append(Edge(q1, q2, ['1']))
q1.edges.append(Edge(q1, q1, ['0', '1']))

q2.edges.append(Edge(q2, q3, ['0', 'epsilon']))

q3.edges.append(Edge(q3, q4, ['1']))

q4.edges.append(Edge(q4, q4, ['0', '1']))

read_state(q0, string, 0, "", F)

for t in threads:
  t.join()
