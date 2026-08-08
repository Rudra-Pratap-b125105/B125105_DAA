set terminal png size 2000,1600
set output 'merge_formula.png'
set title 'Merge Sort vs Modified Merge Sort'
set xlabel 'Input Size (N)'
set ylabel 'n log n'
set grid
plot 'merge_data.txt' using 1:2 with lines lw 2 title 'Merge Sort',\
'merge_data.txt' using 1:3 with lines lw 2 title 'Modified Merge Sort'
pause -1
