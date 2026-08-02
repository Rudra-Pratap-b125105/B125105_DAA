set terminal qt
set terminal png size 1000,800
set output 'toh_for3.png'
set title 'Tower of Hanoi Analysis'
set xlabel 'Number of Discs (n)'
set ylabel 'Total Moves (2^n - 1)'
set grid
set key off
plot 'toh.dat' using 1:2 with linespoints lw 2 pt 7 lc rgb 'blue'
