set datafile separator ','
set grid
set xlabel 'Input Size (n)'
set ylabel 'Execution Time (seconds)'
set terminal pngcairo size 1000,700
set output 'search.png'
set title 'Dictionary - Search Operation'
plot 'search.csv' using 1:2 with linespoints title 'Unsorted Array','search.csv' using 1:3 with linespoints title 'Sorted Array','search.csv' using 1:4 with linespoints title 'Unsorted SLL','search.csv' using 1:5 with linespoints title 'Sorted SLL','search.csv' using 1:6 with linespoints title 'Unsorted DLL','search.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
set terminal pngcairo size 1000,700
set output 'insert.png'
set title 'Dictionary - Insert Operation'
plot 'insert.csv' using 1:2 with linespoints title 'Unsorted Array','insert.csv' using 1:3 with linespoints title 'Sorted Array','insert.csv' using 1:4 with linespoints title 'Unsorted SLL','insert.csv' using 1:5 with linespoints title 'Sorted SLL','insert.csv' using 1:6 with linespoints title 'Unsorted DLL','insert.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
set terminal pngcairo size 1000,700
set output 'delete.png'
set title 'Dictionary - Delete Operation'
plot 'delete.csv' using 1:2 with linespoints title 'Unsorted Array','delete.csv' using 1:3 with linespoints title 'Sorted Array','delete.csv' using 1:4 with linespoints title 'Unsorted SLL','delete.csv' using 1:5 with linespoints title 'Sorted SLL','delete.csv' using 1:6 with linespoints title 'Unsorted DLL','delete.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
set terminal pngcairo size 1000,700
set output 'maximum.png'
set title 'Dictionary - Maximum Operation'
plot 'maximum.csv' using 1:2 with linespoints title 'Unsorted Array','maximum.csv' using 1:3 with linespoints title 'Sorted Array','maximum.csv' using 1:4 with linespoints title 'Unsorted SLL','maximum.csv' using 1:5 with linespoints title 'Sorted SLL','maximum.csv' using 1:6 with linespoints title 'Unsorted DLL','maximum.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
set terminal pngcairo size 1000,700
set output 'minimum.png'
set title 'Dictionary - Minimum Operation'
plot 'minimum.csv' using 1:2 with linespoints title 'Unsorted Array','minimum.csv' using 1:3 with linespoints title 'Sorted Array','minimum.csv' using 1:4 with linespoints title 'Unsorted SLL','minimum.csv' using 1:5 with linespoints title 'Sorted SLL','minimum.csv' using 1:6 with linespoints title 'Unsorted DLL','minimum.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
set terminal pngcairo size 1000,700
set output 'predecessor.png'
set title 'Dictionary - Predecessor Operation'
plot 'predecessor.csv' using 1:2 with linespoints title 'Unsorted Array','predecessor.csv' using 1:3 with linespoints title 'Sorted Array','predecessor.csv' using 1:4 with linespoints title 'Unsorted SLL','predecessor.csv' using 1:5 with linespoints title 'Sorted SLL','predecessor.csv' using 1:6 with linespoints title 'Unsorted DLL','predecessor.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
set terminal pngcairo size 1000,700
set output 'successor.png'
set title 'Dictionary - Successor Operation'
plot 'successor.csv' using 1:2 with linespoints title 'Unsorted Array','successor.csv' using 1:3 with linespoints title 'Sorted Array','successor.csv' using 1:4 with linespoints title 'Unsorted SLL','successor.csv' using 1:5 with linespoints title 'Sorted SLL','successor.csv' using 1:6 with linespoints title 'Unsorted DLL','successor.csv' using 1:7 with linespoints title 'Sorted DLL'
set output
