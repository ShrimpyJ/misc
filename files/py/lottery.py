import random
import sys

multiplier = 5

def find_ticket(ticket, processes):
  count = 0
  for process in processes:
    count += process[1]
    if count >= ticket:
      return process

if len(sys.argv) != 3:
  print("usage: lottery.py num_processes max_iterations")
  quit()

num_processes = int(sys.argv[1])
max_iterations = int(sys.argv[2])

# get number of digits for formatting purposes
temp = num_processes
digits = 1
while int(temp / 10) > 0:
  temp = int(temp / 10)
  digits += 1

max_tickets = 250
processes = []
num_tickets = 0
for i in range(num_processes):
  tickets = random.randint(1, max_tickets)
  iterations = random.randint(0, max_iterations)+1
  processes.append([i, tickets, iterations])
  num_tickets += tickets

print(processes)
print(num_tickets)

while len(processes) > 0:
  if len(processes) == 0:
    break

  r = random.randint(1, num_tickets)
  p = find_ticket(r, processes)

  p[2] -= 1
  if p[2] == 0:
    num_tickets -= p[1]
    processes.remove(p)

print("All processes completed")
