set terminal qt
set title 'Bubble Sort Performance Analysis'
set xlabel 'Array Size (n)'
set ylabel 'Number of Comparisons'
set grid
set key top left
plot 'bubble.dat' using 1:2 with linespoints lw 2 pt 7 title 'Optimized',\
     'bubble.dat' using 1:3 with linespoints lw 2 pt 5 title 'Normal'
