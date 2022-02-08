from random import *
from decimal import *
import datetime
import json
import time
from time import sleep
import threading as thread
import mysql.connector

WEEK = ['MON', 'TUE', 'WED', 'THU', 'FRI', 'SAT', 'SUN']

HOURS = ['6am', '7am', '8am', '9am', '10am', '11am',
         '12am', '1pm', '2pm', '3pm', '4pm', '5pm',
         '6pm', '7pm', '8pm', '9pm', '10pm', '11pm',
         '12pm', '1am', '2am', '3am', '4am', '5am']


# Database: get items by their id as an int
db = mysql.connector.connect(
  host="localhost",
  user="storeowner",
  password="storekey",
  database="store"
)
cursor = db.cursor(buffered=True)
ITEMS = []
cursor.execute('SELECT id from items')

for x in cursor:
  ITEMS.append(str(x))

for i in range(len(ITEMS)):
  ITEMS[i] = int(ITEMS[i][1:len(ITEMS[i])-2])

cursor.close()
db.close()

# Set globals
TICKRATE = 1# / 100000 # In seconds
SECONDS = int(time.time())
TIME = datetime.datetime.now()
DAY = datetime.datetime.fromtimestamp(SECONDS).weekday()
HOUR = ''
DATE = ''
REAL_TIME = 0

TRAFFIC = 0
TRAFFIC_OFFSET = 16   # % for random spread
TRAFFIC_MULT = 1      # Increase/decrease total traffic
EMPLOYEES = 0

MIN_ITEMS = 1
MAX_ITEMS = 250
MIN_FIND_TIME = 15 # In seconds
MAX_FIND_TIME = 30 # In seconds
MIN_SECS_IN_STORE = 5 * 60
MAX_SECS_IN_STORE = 60 * 60

customers = []
threads = []
cond = thread.Condition()
lock = thread.Lock()

class Day():
  def __init__(self, name, num):
    self.name = name
    self.id = num
    self.traffic = []

class Employee():
  def __init__(self, emp_id, start_time, hours):
     self.id = emp_id
     self.conn, self.cur = get_db()
     self.start_time = start_time
     self.hours = hours
     self.end_time = (start_time + hours) % 24
     self.cur.execute("SELECT first_name FROM employees WHERE id=%d" % (self.id))
     for x in self.cur:
       s = str(x)
       self.name = s[3:len(s)-4]
       hour = int(TIME.strftime("%H"))
     print(f"{self.name} clocking in at {self.start_time} for {self.hours} hours.", end=' ')
     print(f"Time is {hour}, leaves at {self.end_time}")

  def work(self):
    while True:
      sleep(TICKRATE)
      if self.check_done():
        break
    self.leave()

  def check_done(self):
    hour = int(TIME.strftime("%H"))
    if hour == self.end_time:
      return True
    return False

  def leave(self):
    global EMPLOYEES
    EMPLOYEES -= 1
    lock.acquire()
    hour = int(TIME.strftime("%H"))
    self.cur.execute("SELECT hourly_rate, hours_worked FROM payroll WHERE employee_id=%d" % (self.id))
    records = self.cur.fetchall()
    wage = 0
    for row in records:
      wage = row[0]
      hours_worked = row[1]
    pay = wage * self.hours
    print(f"{self.name} leaving at {hour}. Paid ${wage}/hr for {self.hours} hours (${pay})")
    self.cur.execute("UPDATE payroll SET hours_worked = hours_worked + %d WHERE employee_id = %d" % (hours_worked, self.id))
    self.cur.execute("INSERT INTO finance (date, sales, wages) VALUES('%s', 0.00, '%lf') ON DUPLICATE KEY UPDATE wages=wages+'%lf'" % (DATE, pay, pay))
    self.conn.commit()
    self.cur.close()
    self.conn.close()
    lock.release()

class Customer():
  def __init__(self, name, conn, cur):
    self.name = name
    self.conn = conn
    self.cur = cur
    self.num_items = randint(MIN_ITEMS, MAX_ITEMS)
    self.list = []
    self.cart = []
    self.time = 0
    self.spent = Decimal(0.00)
    self.ticks = int((self.num_items / MAX_ITEMS) * MAX_SECS_IN_STORE)
    self.ticks += randint(0, 100)
    self.rate = int(self.ticks / self.num_items)
    self.start_time = TIME
    self.end_time =  datetime.datetime.fromtimestamp(SECONDS + self.ticks)
    self.n_items = self.num_items
    for i in range(self.num_items):
      self.list.append(ITEMS[randint(0, len(ITEMS))-1])

  def item_available(self, item):
    lock.acquire()
    self.cur.execute("SELECT stock FROM items WHERE id=%d" % (item))
    for x in self.cur:
      stock = str(x)
    if stock[1] == '0':
      lock.release()
      return False
    lock.release()
    return True

  def add_item(self, item):
    lock.acquire()
    self.cart.append(item)
    #self.cur.execute("UPDATE items SET stock = stock - 1 WHERE id = %d" % (item))
    #self.conn.commit()
    #print(self.cur.rowcount, "record(s) affected")
    lock.release()

  def shop(self):
    while True:
      if TIME >= self.end_time:
        break
      if self.num_items >= 0:
        self.num_items -= 1
        item = self.list[self.num_items]
        if self.item_available(item):
          self.add_item(item)
      self.time += 1
      sleep(TICKRATE)
    self.checkout()

  def checkout(self):
    lock.acquire()
    for item in self.cart:
      self.cur.execute("SELECT price FROM items WHERE id=%d" % (item))
      for x in self.cur:
        price = convert_to_decimal(x)
      #print(f"      {self.name} buying item for {price}")
      self.spent += price
    #print(f"      {self.name} total: {self.spent}")

    self.cur.execute("INSERT INTO finance (date, sales, wages) VALUES('%s', '%lf', 0.00) ON DUPLICATE KEY UPDATE sales=sales+'%lf'" % (DATE, self.spent, self.spent))
    self.conn.commit()
    self.leave()

  def leave(self):
    global TRAFFIC
    print(f"    {self.name} leaving store")
    TRAFFIC -= 1
    self.cur.close()
    self.conn.close()
    lock.release()

def get_db():
  conn = mysql.connector.connect(
    host="localhost",
    user="storeowner",
    password="storekey",
    database="store"
  )
  cur = conn.cursor()
  return conn, cur
    
def convert_to_decimal(decObj):
  decStr = str(decObj)
  decStr = decStr[10:len(decObj)-5]
  return Decimal(decStr)

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
  print(TIME.strftime("%d/%m/%Y %H:%M:%S"), end =' ')
  print(f"Traffic: {TRAFFIC}", end=' ')
  print(f"Employees: {EMPLOYEES}")

def get_time():
  return datetime.datetime.fromtimestamp(SECONDS)

def get_hour():
  hour = int(TIME.strftime("%H"))
  if hour > 12:
    hour -= 12
    hour = str(hour) + 'pm'
  else:
    hour = str(hour) + 'am'
  return hour

def get_date():
  date = TIME.strftime("%Y-%m-%d")
  return date

def get_hour_traffic(days):
  day = find_day(days, WEEK[DAY])
  for hour, t in day.traffic.items():
    if hour == HOUR:
      return t * TRAFFIC_MULT
  return 0

def print_time():
  print("%02d:%02d:%02d" % (TIME[0], TIME[1], TIME[2]))

def clock():
#  global TIME, HOUR, SECONDS, DAY, DATE
#  while True:
#    TIME = get_time()
#    HOUR = get_hour()
#    DATE = get_date()
#    DAY = TIME.weekday()
#    print_now()
#    SECONDS += 1
    sleep(TICKRATE)

def create_customer(names):
  global TRAFFIC
  name = names[randint(0, len(names)-1)]
  conn, cur = get_db()
  c = Customer(name, conn, cur)
  lock.acquire()
  print(f"  Creating new customer {c.name} shopping for {c.num_items} items for {c.ticks} seconds")
  lock.release()
  t = thread.Thread(target=c.shop, args=())
  t.start()
  threads.append(t)
  TRAFFIC += 1

def init_traffic(days, names):
  global TRAFFIC
  day = find_day(days, WEEK[DAY])
  traffic = get_hour_traffic(days)
  if traffic != 0:
    traffic = traffic + randint(0 - TRAFFIC_OFFSET, 0 + TRAFFIC_OFFSET)
  for i in range(traffic):
    create_customer(names)

def create_employee(emp_id, start_time, hours):
  global EMPLOYEES
  EMPLOYEES += 1
  e = Employee(emp_id, start_time, hours)
  t = thread.Thread(target=e.work, args=())
  t.start()
  threads.append(t)

def init_employees(days):
  hour = int(TIME.strftime("%H"))
  day_start = WEEK[DAY].lower() + '_start'
  day_hours = WEEK[DAY].lower() + '_hours'

  conn, cur = get_db()
  cur2 = conn.cursor()

  cur.execute("SELECT id, %s, %s FROM schedules WHERE %s IS NOT NULL" % (day_start, day_hours, day_start))
  records = cur.fetchall()
  for row in records:
    emp_id = row[0]
    start_time = row[1]
    hours = row[2]
    work_hour = start_time
    for i in range(0, hours):
      if work_hour == hour:
        create_employee(emp_id, start_time, hours)
        break
      work_hour = (work_hour + 1) % 24
    cur.close()
    conn.close()

def check_employees(hour):
  conn, cur = get_db()
  day_start = WEEK[DAY].lower() + '_start'
  day_hours = WEEK[DAY].lower() + '_hours'
  cur.execute("SELECT id, %s, %s FROM schedules WHERE %s=%d" % (day_start, day_hours, day_start, hour))
  records = cur.fetchall()
  for row in records:
    create_employee(row[0], row[1], row[2])
  cur.close()
  conn.close()

def start(days, names):
  global TIME, HOUR, SECONDS, DAY, DATE
  secs_in_hour = 3600
  while True:
    TIME = get_time()
    HOUR = get_hour()
    DATE = get_date()
    DAY = TIME.weekday()
    print_now()
    SECONDS += 1

    # Randomly generate new customers
    traffic = get_hour_traffic(days)
    r = randint(0, secs_in_hour)
    if r < traffic:
      create_customer(names)

    # Check for employees clocking in on each hour
    h = int(TIME.strftime("%H"))
    m = int(TIME.strftime("%M"))
    s = int(TIME.strftime("%S"))

    if (m == 0 and s == 0) or (m == 0 and s == 1):
      check_employees(h)

    # Sleep
    sleep(TICKRATE)

days = get_days()
read_traffic(days)
names = read_names()

TIME = get_time()
HOUR = get_hour()
DATE = get_date()

# Initiate employees based on time
init_employees(days)

# Initiate traffic based on time
init_traffic(days, names)

# Start clock
t = thread.Thread(target=clock, args=())
t.start()
threads.append(t)

# Start customer factory
start(days, names)

for thread in threads:
  thread.join()
