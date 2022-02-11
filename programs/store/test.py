def num_upper(s, index, count):
  if index == len(s):
    return count

  if s[index].isupper():
    return num_upper(s, index+1, count+1)

  return num_upper(s, index+1, count+0)

n = num_upper("BoOGaLoOGA", 0, 0)
print(str(n))
