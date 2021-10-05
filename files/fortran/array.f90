program array
implicit none
  integer, dimension (10) :: arr
  integer :: i

  interface
    subroutine fill_array (a)
      integer, dimension(:), intent (out) :: a
      integer :: i
    end subroutine fill_array

    subroutine print_array (a)
      integer, dimension(:) :: a
      integer :: i
    end subroutine print_array
  end interface

  call fill_array(arr)
  call print_array(arr)
end program array

subroutine fill_array(a)
implicit none
  integer, dimension (:), intent (out) :: a

  integer :: i, array_size
  array_size = size(a)

  a(1:3) = 3
  a(4:) = 8

!  do i = 1, array_size
!    a(i) = i
!  end do
end subroutine fill_array

subroutine print_array(a)
implicit none
  integer, dimension (:) :: a
  integer::i, array_size
  array_size = size(a)

  do i = 1, array_size
    print *, a(i)
  end do
end subroutine print_array
