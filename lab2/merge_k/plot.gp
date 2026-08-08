set datafile separator ','
set title 'Comparison of Merging k Sorted Arrays'
set xlabel 'Number of Arrays (k)'
set ylabel 'Execution Time (seconds)'
set grid
set key left top
set style data linespoints
set terminal qt
plot 'output.csv' using 1:2 title 'Method 1 : Sequential Merge' lw 2 pt 7 lc rgb 'blue',\
     'output.csv' using 1:3 title 'Method 2 : Pairwise Merge' lw 2 pt 5 lc rgb 'red'
pause -1
