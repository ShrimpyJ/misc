import os
import sys
from random import *
import string
import requests
import threading
import hashlib
import datetime
import urllib.parse
from faker import Faker

# User info - includes one Card
class User:
    def __init__(self):
        self.name = fake.name()
        self.first = self.name.split(' ')[0]
        self.last = self.name.split(' ')[1]
        self.dobDay = '%02d' % (randint(1, 28))
        self.dobMonth = '%02d' % (randint(1, 12))
        self.dobYear = str(int(datetime.datetime.now().date().strftime("%Y")) - randint(19, 85))
        self.dob = self.dobMonth + '/' + self.dobDay + '/' + self.dobYear
        self.ssn = fake.ssn()
        self.ssn1 = self.ssn.split('-')[0]
        self.ssn2 = self.ssn.split('-')[1]
        self.ssn3 = self.ssn.split('-')[2]

        self.username = self.first.lower() + choice(string.ascii_letters).lower()
        if randint(0, 100) < 60:
            self.username += self.last.lower()
        else:
            self.username += self.dobYear
        email = '@gmail.com' if randint(0, 100) < 70 else '@ymail.com'
        self.email = self.username + email
        self.password = randomPassword()
        self.pin = ''.join(choice(string.digits) for i in range(4))

        addressData = str(fake.address()).splitlines()
        while ',' not in addressData[1]:
            addressData = str(fake.address()).splitlines()
        self.address = addressData[0]
        addressData = addressData[1].split(',')
        self.city = addressData[0]
        self.state = addressData[1].split(' ')[1]
        self.zip = addressData[1].split(' ')[2]
        self.phone = ''.join(choice(string.digits) for i in range(9))
        self.driverID = ''.join(choice(string.digits) for i in range(9))

        self.card = Card()

        self.print()

    def print(self):
        print(f'{self.name} - {self.ssn} - {self.dob} - {self.phone}')
        print(f'{self.username} - {self.email} - {self.password}')
        print(f'{self.address} - {self.state} - {self.city} - {self.zip}')
        print(f'    {self.card.number} - {self.card.exp} - {self.card.cvv}')

# Card info
class Card:
    def __init__(self):
        self.number = fake.credit_card_number()
        self.month = '%02d' % (randint(1, 12))
        self.year = int(datetime.datetime.now().date().strftime("%Y")) + randint(1, 5)
        self.exp = self.month + '/' + str(self.year)
        self.cvv = '%03d' % (randint(1, 999))

# Password generator
def randomPassword():
    chars = string.ascii_letters + string.digits + '!@#$%^&()'
    password = ''.join(choice(chars) for i in range(randint(16, 24)))
    return password

# Thread entry point
def start(url, dataString, method):
    while True:
        user = User()
        data = parseData(dataString, user)
        cookies = parseCookies(cookieString)
    
        # GET or POST
        if method == 'get':
            data = urllib.parse.urlencode(data)
            print(f'GET URL: {url + data}')
            response = requests.get(url + data, allow_redirects=False, cookies=cookies)
        else:
            print(f'POST data: {data}')
            response = requests.post(url, allow_redirects=False, data=data, cookies=cookies)

        print(response)
        if response.status_code == 302:
            print("Request redirected to:", response.headers['Location'])
        print()

# Parse data string of format field1=val1&field2=val2
# vals are checked to determine where to fill in user/card info
def parseData(dataString, user):
    data = {}
    if dataString == '':
        return data

    params = dataString.split('&')  
    for param in params:
        field, val = param.split('=')
        digits = ''.join(ch for ch in val if ch.isdigit())
        if val == 'first':
            val = user.first
        elif val == 'last':
            val = user.last
        elif val == 'first last':
            val = user.name
        elif val == '123':
            val = user.ssn1
        elif val == '45':
            val = user.ssn2
        elif val == '6789':
            val = user.ssn3
        elif digits == '123456789':
            val = user.ssn

        elif val == 'username':
            val = user.username
        elif val == 'password' or val == 'passwordfield' or val == 'Password1@':
            val = user.password
        elif val == 'email' or val == 'email@gmail.com' or val == 'email@ymail.com':
            val = user.email
        elif val == '1234':
            val = user.pin

        elif val == 'city':
            val = user.city
        elif val.upper() in states:
            val = user.state
        elif val == 'address' or val == '123 fake street':
            val = user.address
        elif val == '12345':
            val = user.zip
        elif digits == '5555555555':
            val = user.phone

        elif digits == '01012000':
            val = user.dob
        elif val == '4' or val == '04':
            val = user.dobMonth
        elif val == '20':
            val = user.dobDay
        elif val == '2000':
            val = user.dobYear

        elif digits == '0000000000000000' or digits == '1111222233334444' or digits == '4251378250945803':
            val = user.card.number
        elif digits in exps:
            val = user.card.exp
        elif val in months:
            val = user.card.month
        elif val in years:
            val = user.card.year
        elif val == '666':
            val = user.card.cvv
        elif digits == '987654321':
            val = user.driverID

        data[field] = val

    return data

# Parse cookie string of format field1=val1&field2=val2
def parseCookies(cookieString):
    cookies = {}
    if cookieString == '':
        return cookies
    params = cookieString.split('&')
    for param in params:
        field, val = param.split('=')
        cookies[field] = val
    return cookies

# Print help
argc = len(sys.argv)
argv = sys.argv
if argc == 1 or argv[1] == '-h' or argv[1] == '--help':
    print('usage: python3 scam.py -u [URL]')
    print('  Default method is GET and uses only URL.')
    print('  For POST, add --data [DATA]')
    print('Flags:')
    print('  -t,  --threads    Thread count')
    print('  -c,  --cookies    Cookie data')
    print('  -d,  --data       POST Data')
    print('                      name of fields determined by searching for following keywords:')
    print('         First Name:    first')
    print('          Last Name:    last')
    print('          Full Name:    first last')
    print('                DOB:    04/20/2000 (month=4, day=20, year=2000)')
    print('                SSN:    123-45-6789')
    print('            ATM PIN:    1234')
    print('            Address:    address OR 123 fake street')
    print('               City:    city')
    print('              State:    ANY TWO-LETTER U.S. STATE CODE')
    print('                Zip:    12345')
    print('           Username:    username')
    print('           Password:    password OR passwordfield OR Password1@')
    print('              Email:    email@gmail.com OR email@ymail.com OR email')
    print('             Card #:    0000000000000000 OR 1111222233334444 OR 4251378250945803')
    print('           Card Exp:    01/2000 THRU 12/2999')
    print('           Card CVV:    666')
    print('     Driver License:    987654321')
    print('                      any remaining fields will be set to provided values')
    quit()

# Setup data arrays
states = [
    'AL', 'AK', 'AZ', 'AR', 'CA', 'CO', 'CT', 'DE', 'FL', 'GA',
    'HI', 'ID', 'IL', 'IN', 'IA', 'KS', 'KY', 'LA', 'ME', 'MD',
    'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'NE', 'NV', 'NH', 'NJ',
    'NM', 'NY', 'NC', 'ND', 'OH', 'OK', 'OR', 'PA', 'RI', 'SC', 
    'SD', 'TN', 'WI', 'WY' ]
months = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']
years = []
for i in range(2000, 3000):
    years.append(str(i))
exps = []
for month in months:
    for year in years:
        exps.append(month + year)

fake = Faker()

# Setup defaults
url = ''
dataString = ''
cookieString = ''
method = 'get'
threadc = 1

# Set defaults based on arguments
for i, arg in enumerate(argv):
    arg = arg.lower()
    if arg == '-u' or arg == '--url':
        if i+1 == argc:
            print('-u flag must specify URL')
            quit()
        url = argv[i+1]
    if arg == '-d' or arg == '--data':
        method = 'post'
        if i+1 == argc:
            print('-d flag must specify data')
            quit()
        dataString = argv[i+1]
    if arg == '-t' or arg == '--threads':
        if i+1 == argc:
            print('-t flag must specify thread count')
            quit()
        threadc = int(argv[i+1])
    if arg == '-c' or arg == '--cookies':
        if i+1 == argc:
            print('-c flag must specify cookie data')
            quit()
        cookieString = argv[i+1]

if method == 'get':
    dataString = url.split('?')[1]

# Start threads
threads = []
for i in range(threadc):
    t = threading.Thread(target=start, args=(url, dataString, method))
    t.daemon = True
    threads.append(t)

for i in range(threadc):
    threads[i].start()

for i in range(threadc):
    threads[i].join()
