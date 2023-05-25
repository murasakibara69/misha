program calculator

  implicit none

  real :: a, b
  integer :: plus_pos, minus_pos
  character, parameter :: plus = "+", minus = "-"
  character(len=256) :: str

  read"(A)", str
  plus_pos = index(str, plus)
  read(str(1:plus_pos-1), *) a
  read(str(plus_pos+1:len(str)), *) b
  print*, a + b
  
end program calculator
