program test

  use, intrinsic :: iso_fortran_env, only: wp => real64

  implicit none

  integer :: ios

  open(unit=101, file="out", iostat=ios, status="old", action="write")
  if (ios /= 0) stop "Error opening file"

  write(101, *) "pasha"

  close(101)

  
end program test
