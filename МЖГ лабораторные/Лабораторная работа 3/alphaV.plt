set xlabel "α, град"
set ylabel "V_{ТА}, м/с"
set grid
set nokey
set terminal pngcairo size 600, 400
set output "alphaV.png"
plot "alphaV.dat" u 2:3 w lp pt 7 
