# --- Part 1: Compare obs ---

# Set output png_filename, size 
set terminal pngcairo size 800,600 font "Arial,10"
set output 'merges
ort_caso_medio.png'

#  Set title
set title "MergeSort - Caso Medio"

# Set label
set xlabel "Tamaño array(N)"
set ylabel "OBs"

# Add grid
set grid

# Set location of legend
set key top left

# Plot using obs as y axis
plot 'exercise5_mergesort.log' using 1:2 with linespoints title 'MergeSort'

set output 'quicksort_caso_medio.png'
# Plot using obs as y axis
plot 'exercise5_mergesort.log' using 1:2 with linespoints title 'QuickSort'

#2.Compare diferent versions of QuickSort