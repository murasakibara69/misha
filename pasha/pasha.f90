program pashar

  implicit none

  character(8) :: string

  read(*,*) string

  if(string.eq."pasha") then
    write(*,*) "gavno"
  else if(string.eq."bylovich") then
    write(*,*) "polnaya hyinia" 
  else if(string.eq."matvey") then
    write(*,*) "shar"
  else if(string.eq."ilya") then
    write(*,*) "nefor, hui, huesos, pidor, chmo, pasha"
  else
    write(*,*) "good"
  end if

end program
