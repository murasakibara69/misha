program pyvel

use, intrinsic :: iso_fortran_env, only : wp => int128

  implicit none
  
  integer, parameter :: a = 120000000000000000, b = 310000000000000000000
  integer :: c
  character(len=256) :: str, pasha

  integer :: ios, io

  io = 101
  c = a + b
  pasha = "pasha"
  open(unit=io, file='pasha', iostat=ios, status="replace", action="write", iomsg=str)
  if (ios /= 0) stop trim(str)
  write(io, *) c, trim(pasha)
  close(io)

end program pyvel
