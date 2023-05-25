program first

  use, intrinsic :: iso_fortran_env, only: wp => real128

  implicit none
  
  integer, parameter :: io = 12
  character(len=256) :: str
  real(wp), parameter :: pi = 4.0_wp * atan(1.0_wp)

  integer :: ios

  open(unit=io, file='pasha', iostat=ios, status="old", action="read", iomsg=str)
  if (ios /= 0) then
    print"(a, i0)", "ios = ", ios
    print"(a)", trim(str)
    stop
  end if

end program first
