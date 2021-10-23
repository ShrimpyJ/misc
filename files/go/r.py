def r(n):
  print(n)
  if n == 0:
    return 3
  return r(n-1) * 5 + 9

print(r(1))
