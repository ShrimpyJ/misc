from random import *

f = open('employees.csv')
lines = f.read().splitlines()
max_hours = 40
min_hours = 10

for line in lines:
  
