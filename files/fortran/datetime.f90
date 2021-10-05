program datetime
implicit none

  character(len = 8) :: dateinfo ! ccyymmdd
  character(len = 4) :: year, month*2, day*2

  character (len = 10) :: timeinfo
  character (len = 2) :: hour, minute, second*6

  call date_and_time(dateinfo, timeinfo)

  year = dateinfo(1:4)
  month = dateinfo(5:6)
  day = dateinfo(7:8)

  print*, 'Date String: ', dateinfo
  print*, 'Year: ', year
  print *, 'Month: ', month
  print *, 'Day: ', day

end program datetime
