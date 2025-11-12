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

#5. Gráfica comparando los tiempos mejor peor y medio en OBs para QuickSort
f(x)=a*x*log(x)+b

set output 'quicksort_first_best_mean_worst_obs.png'
set title "QuickSort(First)"

fit f(x) 'exercise5_quicksort.log' using 1:5 via a,b 
plot 'exercise5_quicksort.log' using 1:3 with linespoints title 'QuickSort-ObsPromedio', \
     'exercise5_quicksort.log' using 1:4 with linespoints title 'QuickSort-ObsMaximo', \
     'exercise5_quicksort.log' using 1:5 with linespoints title 'QuickSort-ObsMinimo', \
    f(x) with lines lw 2 title sprintf("%.2e*n*log(n)+%.2e", a,b)

#5.Gráfica comparando el tiempo medio de reloj de Quicksort usando los pivotes median, median_avg y median_stat.
set output 'quicksort_all_pivote_caso_medio.png'
set title "QuickSort(First/MedianAvg/MediaStat) - Caso Medio"
g(x)=c*x*log(x)+d
fit g(x) 'exercise5_quicksort.log' using 1:2 via c,d

set ylabel "tiempo"
set xrange [1:10000]
plot 'exercise5_quicksort.log' using 1:2 with linespoints title 'QuickSort First', \
    'exercise5_quicksort_median_avg.log' using 1:2 with linespoints title 'QuickSort MedianAvg',\
    'exercise5_quicksort_median_stat.log' using 1:2 with linespoints title 'QuickSort MedianStat',\
    g(x) with lines lw 2 title sprintf("%.2e*n*log(n)+%.2e", c,d)

#5.Gráfica con el tiempo medio de reloj para QuickSort, comentarios a la gráfica.
set output 'quicksort_first_pivote_mean_time.png'
set title "QuickSort(First) - Tiempo Medio"
plot 'exercise5_quicksort.log' using 1:2 with linespoints title 'QuickSort First',\
    g(x) with lines lw 2 title sprintf("%.2e*n*log(n)+%.2e", c,d)

#5.Grafica comparando el tiempo medio de reloj de MergeSort y QuickSort
set output 'quicksort_mergesort_mean_time.png'
set title "QuickSort-MergeSort - Tiempo Medio"
set xrange [1:10000]
h(x)=e*x*log(x)+f
fit h(x) 'exercise5_quicksort.log' using 1:2 via e,f
plot 'exercise5_quicksort.log' using 1:2 with linespoints title 'QuickSort First',\
     'exercise5_mergesort.log' using 1:2 with linespoints title 'MergeSort',\
    h(x) with lines lw 2 title sprintf("%.2e*n*log(n)+%.2e", e,f)
