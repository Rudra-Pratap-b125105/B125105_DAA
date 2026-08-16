set terminal png size 1000,600
set output 'time_vs_n.png'
set title 'Special Matrix Multiplication - Time vs n'
set xlabel 'Input Size (n)'
set ylabel 'Execution Time (seconds)'
set grid
set logscale x 2
plot 'special_matrix_results.dat' using 1:3 with linespoints lw 2 title 'Measured Time'
set output 'time_vs_n_squared.png'
set title 'Validation of O(n^2): Time vs n^2'
set xlabel 'n^2'
set ylabel 'Execution Time (seconds)'
unset logscale x
set grid
C = 3.824157714844e-08
theory(x) = C*x
plot 'special_matrix_results.dat' using 2:3 with linespoints lw 2 title 'Measured Time', \ 
     theory(x) with lines lw 2 title 'Theoretical C*n^2'
set output 'time_ratio_vs_n.png'
set title 'Validation of O(n^2): Time / n^2 vs n'
set xlabel 'Input Size (n)'
set ylabel 'Time / n^2'
set logscale x 2
set grid
plot 'special_matrix_results.dat' using 1:4 with linespoints lw 2 title 'Measured Time / n^2'
