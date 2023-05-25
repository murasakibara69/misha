program pasha 

use, intrinsic :: iso_fortran_env, only: wp => real128

  implicit none
  real(wp) :: a
  read*, a
  if (a.eq.0.0_wp) then
    print*, "matvyrlok"
  else 
    print*, "ilnyrlok"
  end if
  

end program pasha
