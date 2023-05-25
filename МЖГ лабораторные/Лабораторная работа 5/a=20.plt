set xlabel "s̄"
set ylabel "p̄"
set grid
set terminal pngcairo size 600, 400
set output "a=20.png"
set key bottom right 
plot "a=201.dat" u 2:8 w lp pt 7 title "вверх профиля", "a=202.dat" u 2:8 w lp pt 7 title "низ профиля" 
