set xlabel "α, град"
set ylabel "f(α)_{с.н.}"
set yrange [0.7:1.05]
set grid
set nokey
set terminal pngcairo size 600, 400
set output "alphaA.png"
plot "alphaA.dat" u 2:8 w lp pt 7 
