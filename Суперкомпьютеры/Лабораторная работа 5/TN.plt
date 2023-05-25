set ylabel "T, с"
set xlabel "N"
set grid
set nokey
set terminal pngcairo size 600, 400
set output "TN.png"
plot "TN.dat" u 1:2 w p pt 7 
