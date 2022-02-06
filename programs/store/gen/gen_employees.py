from random import *

numDep = 8

f = open('names.txt')
names = f.read().splitlines()

print('id,first_name,last_name,department_id')
ID = 1
DEP = 1

# Produce
for i in range(5):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
# Dairy
for i in range(5):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
# Deli
for i in range(5):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
# Bakery
for i in range(5):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
# Meat
for i in range(6):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
# Ambient
for i in range(4):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
# Frozen
for i in range(3):
  first = names[randint(0,len(names)-1)]
  last = names[randint(0,len(names)-1)]
  print(f'{ID},"{first}","{last}",{DEP}')
  ID += 1
DEP += 1
