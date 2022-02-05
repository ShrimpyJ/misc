from random import *
import datetime
import json
import time
from time import sleep
import threading as thread

WEEK = ['MON', 'TUE', 'WED', 'THU', 'FRI', 'SAT', 'SUN']

HOURS = ['6am', '7am', '8am', '9am', '10am', '11am',
         '12am', '1pm', '2pm', '3pm', '4pm', '5pm',
         '6pm', '7pm', '8pm', '9pm', '10pm', '11pm',
         '12pm', '1am', '2am', '3am', '4am', '5am']

TICKRATE = 1
TIME = datetime.datetime.now()
DAY = datetime.datetime.today().weekday()
HOUR = '6am'

TRAFFIC = 0
TRAFFIC_OFFSET = 16   # % for random spread
TRAFFIC_MULT = 3      # Increase/decrease total traffic

MIN_ITEMS = 1
MAX_ITEMS = 250
MIN_SECS_IN_STORE = 5 * 60
MAX_SECS_IN_STORE = 30 * 60

customers = []
threads = []

class Day():
  def __init__(self, name, num):
    self.name = name
    self.id = num
    self.traffic = []

class Customer():
  def __init__(self, name):
    self.name = name
    self.num_items = randint(MIN_ITEMS, MAX_ITEMS)
    self.list = []
    self.cart = []
    self.spent = 0.0
    self.ticks = int((self.num_items / MAX_ITEMS) * MAX_SECS_IN_STORE)
#    if self.ticks < MIN_SECS_IN_STORE:
#      self.ticks = MIN_SECS_IN_STORE
    self.rate = int(self.ticks / self.num_items)

  def shop(self):
    while self.ticks > 0 and self.num_items > 0:
      if self.ticks % self.rate == 0:
        self.num_items -= 1
        #print(f"{self.name} buying ITEM. Now has {self.num_items} items left to buy")
      self.ticks -= 1
      sleep(TICKRATE)
    self.leave()

  def leave(self):
    global TRAFFIC
    print(f"    {self.name} leaving store with {self.num_items} items left to buy and {self.ticks} seconds")
    TRAFFIC -= 1
    

def read_names():
  f = open('names.txt')
  names = f.read().splitlines()
  return names

def find_day(days, name):
  for day in days:
    if day.name == name:
      return day

def read_traffic(days):
  f = open('info.json')
  data = json.load(f)

  for i in data['traffic']:
    day = find_day(days, i['day'])
    day.traffic = i['customers']

  f.close()

def get_days():
  days = []
  for i in range(len(WEEK)):
    days.append(Day(WEEK[i], i))
  return days

def get_current_day():
  return datetime.datetime.today().weekday()

def now():
  return datetime.datetime.now()

def print_now():
  print(WEEK[DAY], end=' ')
  print(TIME.strftime("%d/%m/%Y %H:%M:%S"), end = ' ')
  print(f"Traffic: {TRAFFIC}")

def get_timestamp(seconds):
  return str(datetime.timedelta(seconds = seconds))

def get_hour():
  hour = int(TIME.strftime("%H"))
  if hour > 12:
    hour -= 12
    hour = str(hour) + 'pm'
  else:
    hour = str(hour) + 'am'
  return hour

def get_hour_traffic(days):
  day = find_day(days, WEEK[DAY])
  for hour, t in day.traffic.items():
    if hour == HOUR:
      return t * TRAFFIC_MULT
  return 0

def clock():
  global TIME, HOUR
  while True:
    TIME = now()
    print_now()
    HOUR = get_hour()
    sleep(TICKRATE)

def create_customer(names):
  global TRAFFIC
  name = names[randint(0, len(names)-1)]
  c = Customer(name)
  print(f"  Creating new customer {c.name} shopping for {c.num_items} items for {c.ticks} seconds")
  customers.append(c)
  t = thread.Thread(target=c.shop, args=())
  t.start()
  threads.append(t)
  TRAFFIC += 1

def customer_factory(days, names):
  secs_in_hour = 3600
  while True:
    traffic = get_hour_traffic(days)
    r = randint(0, secs_in_hour)
    if r < traffic:
      create_customer(names)
    sleep(TICKRATE)

def init_traffic(days, names):
  global TRAFFIC
  day = find_day(days, WEEK[DAY])
  traffic = get_hour_traffic(days)
  num = traffic + randint(0 - TRAFFIC_OFFSET, 0 + TRAFFIC_OFFSET)
  for i in range(num):
    create_customer(names)

days = get_days()
read_traffic(days)
names = read_names()

TIME = now()
HOUR = get_hour()

# Initiate traffic based on time
init_traffic(days, names)
print("TRAFFIC: ", TRAFFIC)

# Start clock
t = thread.Thread(target=clock, args=())
t.start()
threads.append(t)

# Start customer factory
customer_factory(days, names)

for thread in threads:
  thread.join()
