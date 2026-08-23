set datafile separator ','
set title 'Linear Time Validation of Colour Sorting'
set xlabel 'Input Size (n)'
set ylabel 'Execution Time (ms)'
set grid
set key top left
plot 'sorting_data.csv' using 1:2 with linespoints title 'Measured Time'
