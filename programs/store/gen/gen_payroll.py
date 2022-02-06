from random import *

min_rate = 8.85
max_rate = 14.55

f = open('employees.csv')
lines = f.read().splitlines()
num_emp = len(lines)-1

print("employee_id,hourly_rate,hours_worked")
for i in range(num_emp):
  r = randint(min_rate*100,max_rate*100)
  r = r
  while r % 5 != 0:
    r += 1
  r = float(r / 100)
  print(str(i+1) + "," + "%.2f,0" % (r))
