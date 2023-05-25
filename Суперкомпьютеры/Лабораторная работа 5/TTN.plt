set ylabel "T, с"
set xlabel "TN"
set grid
set nokey
set terminal pngcairo size 600, 400
set output "TTN.png"
plot "TTN.dat" u 1:2 w p pt 7 
