set xlabel "s̄"
set ylabel "p̄"
set grid
set terminal pngcairo size 600, 400
set output "a=10.png"
set key bottom right 
plot "a=101.dat" u 2:8 w lp pt 7 title "вверх профиля", "a=102.dat" u 2:8 w lp pt 7 title "низ профиля" 
