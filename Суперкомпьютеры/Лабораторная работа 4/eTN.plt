set ylabel "e=a/TN"
set xlabel "TN"
set grid
set nokey
set terminal pngcairo size 600, 400
set output "eTN.png"
plot "eTN.dat" u 1:2 w p pt 7 
