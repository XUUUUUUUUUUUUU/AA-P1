# --- Part 1: Compare average time ---

# Set output png_filename, size 
set terminal pngcairo size 800,600 font "Arial,10"
set output 'comparison_mean_time.png'

#  Set title
set title "InsertSort vs. BubbleSort - Tiempo Medio"

# Set label
set xlabel "Tamaño array(N)"
set ylabel "Tiempo (segundos)"

# Add grid
set grid

# Set location of legend
set key top left

# Plot using time as y axis
plot 'exercise5.log' using 1:2 with linespoints title 'InsertSort', \
     'exercise6.log' using 1:2 with linespoints title 'BubbleSort'

# --- Part 2: Compare Obs mean ---

# Set output filename and title
set output 'comparison_mean_ob.png'
set title "InsertSort vs. BubbleSort - OBs medio"
set ylabel "Obs medio"

# Plot using average_ob as y-axis
plot 'exercise5.log' using 1:3 with linespoints title 'InsertSort OBs', \
     'exercise6.log' using 1:3 with linespoints title 'BubbleSort OBs'

#--- Part 3: Compare best case time ---
set output 'comparison_best_case_time.png'
set title " InsertSort vs. BubbleSort - Best case time"
set ylabel "Tiempo (segundos)"

# Plot using best_case time as y-axis
plot 'insertsort.log' using 1:2 with linespoints title 'InsertSort BestTimes', \
     'bubblesort.log' using 1:2 with linespoints title 'BubbleSort BestTimes'

#--- Part 4: Compare worst case time ---
set output 'comparison_worst_case_time.png'
set title " InsertSort vs. BubbleSort - Worst case time"
set ylabel "Tiempo (segundos)"

# Plot using worst case time as y-axis
plot 'insertsort.log' using 1:3 with linespoints title 'InsertSort WorstTimes', \
     'bubblesort.log' using 1:3 with linespoints title 'BubbleSort WorstTimes'

#--- Part 5: Mean Ob of Insert Sort ---
# Set output filename and title
set output 'insertsort_mean_ob.png'
set title "InsertSort - OBs medio"
set ylabel "Obs medio"

# Plot using average_ob as y-axis
plot 'exercise5.log' using 1:3 with linespoints title 'InsertSort OBs'

#--- Part 6: Insert Sort: Best and worst time---
# Set output filename and title
set output 'insertsort_best_worst_time.png'
set title "InsertSort - Best and worst time"
set ylabel "Tiempo (segundos)"

# Plot using time as y-axis
plot 'insertsort.log' using 1:2 with linespoints title 'InsertSort Best case',\
     'insertsort.log' using 1:3 with linespoints title 'InsertSort Worst case'

#--- Part 7: Insert Sort: Mean time---
# Set output filename and title
set output 'insertsort_mean_time.png'
set title "InsertSort - Mean time"
set ylabel "Tiempo (segundos)"

# Plot using time as y-axis
plot 'exercise5.log' using 1:2 with linespoints title 'InsertSort Average case'

#--- Part 8: Insert Sort con ajustes  ---
#Ajustamos una función cuadrático para Insert en el caso mejor y peor.
f(x)=a*x +b 
a=1;b=1
fit f(x) 'insertsort.log' using 1:2 via a,b
set output 'insert_sort_bc_adjust.png'
set title "Insert Sort: Best case(with adjust O(N))"

plot 'insertsort.log' using 1:2 with linespoints title 'InsertSort Best Case', \
     f(x) with lines lw 2 title sprintf("Adjust is (a=%.2e)", a)

#caso peor
g(x)=c*x**2+d*x+e
c=1;d=1;e=1;
fit g(x) 'insertsort.log' using 1:3 via c,d,e 

set output 'insert_sort_wc_adjust.png'
set title "Insert Sort: Worst case(with adjust O(N^2))"

plot 'insertsort.log' using 1:3 with linespoints title 'InsertSort Worst Case', \
     g(x) with lines lw 2 title sprintf("Adjust is (c=%.2e)", c)

#--- Part 9: Bubble Sort con ajustes  ---
#Ajustamos una función cuadrático para BubbleSort en el caso mejor y peor.
a=1;b=1
fit f(x) 'bubblesort.log' using 1:2 via a,b
set output 'bubblesort_sort_bc_adjust.png'
set title "Bubble Sort: Best case(with adjust O(N))"

plot 'bubblesort.log' using 1:2 with linespoints title 'BubbleSort Best Case', \
     f(x) with lines lw 2 title sprintf("Adjust is (a=%.2e)", a)

#caso peor
c=1;d=1;e=1;
fit g(x) 'bubblesort.log' using 1:3 via c,d,e 

set output 'bubble_sort_wc_adjust.png'
set title "Bubble Sort: Worst case(with adjust O(N^2))"

plot 'bubblesort.log' using 1:3 with linespoints title 'BubbleSort Worst Case', \
     g(x) with lines lw 2 title sprintf("Adjust is (c=%.2e)", c)
