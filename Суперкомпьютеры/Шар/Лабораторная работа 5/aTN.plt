set ylabel "a"
set xlabel "TN"
set grid
set nokey
set terminal pngcairo size 600, 400
set output "aTN.png"
plot "aTN.dat" u 1:2 w p pt 7 
