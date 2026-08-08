set datafile separator ','
set title 'Dictionary Search Operation'
set xlabel 'Input Size (n)'
set ylabel 'Execution Time (seconds)'
set grid
set key outside
set style data linespoints
set terminal qt
set terminal png size 1000,800
set output 'dict.png'
plot 'output.csv' using 1:2 title 'Unsorted Array' lw 2 pt 7,\
'output.csv' using 1:3 title 'Sorted Array' lw 2 pt 5,\
'output.csv' using 1:4 title 'Unsorted SLL' lw 2 pt 9,\
'output.csv' using 1:5 title 'Sorted SLL' lw 2 pt 11,\
'output.csv' using 1:6 title 'Unsorted DLL' lw 2 pt 13,\
'output.csv' using 1:7 title 'Sorted DLL' lw 2 pt 15
pause -1
