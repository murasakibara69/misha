program calculator

  use, intrinsic :: iso_fortran_env, only: wp => real32
  
  implicit none
  
  real(wp) :: a, b
  integer :: pos
  character(len=50) :: str
  character, dimension(*), parameter :: symbol = ['+', '-', '*', '/']
  character :: final_symbol

  integer :: i

  write(*, *)
  
  do while (.true.)
    
    write(*, "(A)", advance = "no") ">>> "
    read"(A)", str
    if (str.eq."exit") exit
    
    pos = 0
    do i = 1, size(symbol, dim=1)
      if (index(str, symbol(i)).ne.0) then
        pos = index(str, symbol(i))
        exit
      end if
    end do
    if (pos.eq.0) then 
      print"(A)", "Invalid expression"
      cycle
    end if
    
    call str_to_real(str, pos, a, b)
    
    final_symbol = symbol(i)
    if (final_symbol.eq.'+') then
      print*, a + b
    elseif (final_symbol.eq.'-') then
      print*, a - b
    elseif (final_symbol.eq.'*') then
      print*, a * b
    else
      if (b.eq.0.0_wp) then
        print"(A)", "Pasha"
      else
        print*, a/b
      end if
    end if
    
  end do
   
contains
  
  subroutine str_to_real(str, pos, a, b)
    character(len=*), intent(in) :: str
    integer, intent(in) :: pos
    real(wp), intent(inout) :: a, b
    read(str(1:pos-1), *) a
    read(str(pos+1:len(str)), *) b
  end subroutine str_to_real
  
end program calculator
