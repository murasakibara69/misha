set xlabel "α, град"
set ylabel "f(α)_{v.}"
set grid
set nokey
set yrange [:1.02]
set terminal pngcairo size 600, 400
set output "alphasqrtA.png"
plot "alphasqrtA.dat" u 2:8 w lp pt 7 
