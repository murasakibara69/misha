program pyvel

  use, intrinsic :: iso_fortran_env, only: wp => real64

  implicit none
  
  real(wp) :: a, b, c
  character(256) :: r, str
  
  print*, "calculate:"
  read*, a, r, b
  if (r.eq."+") then
  write(*, *) a + b
  else if (r.eq."-") then
  write(*, *) a - b
  else if (r.eq."*") then
  write(*, *) a * b
  else if (r.eq."\") then
  if (b.eq.0.0_wp) then
  write(*, *) "Idi nahui"
  else 
  write (*, *) a / b
  end if
  end if

end program pyvel
