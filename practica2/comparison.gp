# --- Part 1: Compare obs ---

# Set output png_filename, size 
set terminal pngcairo size 800,600 font "Arial,10"


set output 'mergesort_caso_medio.png'
set title "MergeSort - Caso Medio"
set xlabel "Tamaño array(N)"
set ylabel "OBs"

set grid
set key top left

# Plot using obs as y axis
plot 'exercise5_mergesort.log' using 1:2 with linespoints title 'MergeSort'

# Mean case using the first element of array as pivote 
f(x)=a*x*log(x)

set output 'quicksort_first_caso_medio.png'
set title "QuickSort(First) - Caso Medio"


# Plot using obs as y axis
fit f(x) 'exercise5_quicksort.log' using 1:3 via a 
plot 'exercise5_quicksort.log' using 1:3 with linespoints title 'QuickSort', \
    f(x) with lines lw 2 title sprintf("a*n*log(n):Adjust is (a=%.2e)", a)

#2.Compare diferent versions of QuickSort
set output 'quicksort_all_pivote_caso_medio.png'
set title "QuickSort(First/MedianAvg/MediaStat) - Caso Medio"

plot 'exercise5_quicksort.log' using 1:3 with linespoints title 'QuickSort First', \
    'exercise5_quicksort_median_avg.log' using 1:3 with linespoints title 'QuickSort MedianAvg',\
    'exercise5_quicksort_median_stat.log' using 1:3 with linespoints title 'QuickSort MedianStat'