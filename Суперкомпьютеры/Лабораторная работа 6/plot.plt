set xlabel "{/Symbol x}"
set ylabel "{/Symbol h}"
set zlabel "{/Symbol w}"
set nokey
set ticslevel 0.2
set terminal pngcairo enhanced font "arial,10" fontscale 1.0 size 600, 400 
set output "poisson.png"
splot "result.dat" w p palette
