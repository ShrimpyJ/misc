import os
import threading
from sys import stdin
import time

FAIL = "./failed.txt"
destination = "./downloads"
time = 0.2
whitelist = ['a','b','c','d','e','f','g','h','i','j','k','l','m',
             'n','o','p','q','r','s','t','u','v','w','x','y','z',
             'A','B','C','D','E','F','G','H','I','J','K','L','M',
             'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
             '0','1','2','3','4','5','6','7','8','9',
             ' ', '\'']

lines = []
for line in stdin:
  if line == '':
    break
  lines.append(line)

def check_failed(line):
  failed = open(FAIL, 'r')
  contents = failed.readlines()
  for content in contents:
    if content == line:
      return 1
  return 0

def in_whitelist(c):
  for w in whitelist:
    if c == w:
      return 1
  return 0

failed = open(FAIL, 'w')
failed.close()

for line in lines:
  s = "\""
  for c in line:
    if(in_whitelist(c)):
      s += c
  s = " ".join(s.split())
  s += "\""
  s = s.lower()

  cmd = 'echo 1 | soulseek download ' + s + ' --quality=320 --mode=mp3 --destination=' + destination
  ret = os.system(cmd)
  print("Returned: " + str(ret))
  if ret != 0:
    cmd = 'echo 1 | soulseek download ' + s + ' --mode=mp3 --destination=' + destination
    ret = os.system(cmd)
    print("Returned: " + str(ret))
    if ret != 0:
      failed = open(FAIL, 'a')
      print("Writing as failed: " + line, end='')
      failed.write(line)
      failed.close()

cmd = 'bash clean.sh'
os.system(cmd)
