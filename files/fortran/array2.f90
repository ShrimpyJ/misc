program dynamic_array
implicit none
  real, dimension (:,:), allocatable :: darray
  integer :: s1, s2
  integer :: i, j

  print*, "Enter size of array:"
  read*, s1, s2

  allocate( darray(s1,s2) )

  do i = 1, s1
    do j = 1, s2
      darray(i,j) = i*j
      print*, "darray(",i,",",j,") = ", darray(i,j)
    end do
  end do

  deallocate(darray)
end program dynamic_array
