program trim_string
implicit none

  character (len = *), parameter :: fname="Susanne", sname="Rizawn"
  character (len = 20) :: fullname
  character (len = 10) :: test

  fullname = fname//" "//sname
  fullname = trim(fullname)

  print*, fullname, ", the beautiful dancer from the east!"
  print*, trim(fullname), ", the beautiful dancer from the east!"

  test = 'awn'

  if (index(fullname, test) == 0) then
    print *, 'test ', test, ' is not found'
  else
    print *, 'test ', test, ' is found at index: ', index(fullname, test)
  end if

end program trim_string
