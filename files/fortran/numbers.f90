program numbers
  implicit none

  ! integer widths
  integer(kind = 2) :: shortval
  integer(kind = 4) :: longval
  integer(kind = 8) :: verylongval
  integer(kind = 16) :: veryverylongval
  integer :: def

  ! floating point
  real :: a, b, result

  ! boolean
  logical :: done

  ! character
  character(len=80) :: message


  ! print ints
  print *, huge(shortval), '    ', kind(shortval)
  print *, huge(longval)
  print *, huge(verylongval)
  print *, huge(veryverylongval)
  print *, huge(def)

  ! print float
  a = 12.0
  b = 15.0
  result = a + b
  print *, 'The total is ', result

  ! print boolean
  done = .true.
  print *, done

  ! print character
  message = "This is a message"
  print *, message
  print *, message(11:7)

end program numbers
