set xlabel "s̄_i"
set ylabel "p̄_i"
set grid
set terminal pngcairo size 600, 400
set output "pasha8.png"
set key right top
plot "murlok1.dat" u 2:7 w lp pt 7 title "верх трубки", "murlok2.dat" u 2:7 w lp pt 7 dt 2 title "низ трубки"
