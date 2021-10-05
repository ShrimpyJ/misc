time32 = 2147483647
utime32 = 4294967295
time64 = 9223372036854775807
utime64 = 18446744073709551615

start_year = 1970
sec_in_year = 31557600

def calc_year(t, year):
  return int(start_year + (t / sec_in_year))

end = calc_year(time32, start_year)
begin = start_year - (end - start_year)
print("Year range for 32-bit signed int  : " + str(begin) + " to " + str(end))
end = calc_year(utime32, start_year)
begin = start_year
print("Year range for 32-bit unsigned int: " + str(begin) + " to " + str(end))

end = calc_year(time64, start_year)
begin = start_year - (end - start_year)
print("Year range for 64-bit signed int  : " + str(begin) + " to " + str(end))
end = calc_year(utime64, start_year)
begin = start_year
print("Year range for 64-bit unsigned int: " + str(begin) + " to " + str(end))
