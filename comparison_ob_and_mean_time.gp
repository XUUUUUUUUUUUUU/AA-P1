# --- Part 1: Compare average time ---

# Set output png_filename, size 
set terminal pngcairo size 800,600 font "Arial,10"
set output 'comparison_mean_time.png'

#  Set title
set title "InsertSort vs. BubbleSort - Tiempo Medio"

# Set label
set xlabel "Tamaño array(N)"
set ylabel "Tiempo medio(segundos)"

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

# Plot using average_ob as y axis
plot 'exercise5.log' using 1:3 with linespoints title 'InsertSort OBs', \
     'exercise6.log' using 1:3 with linespoints title 'BubbleSort OBs'

# End of script
print "Picture 'comparison_mean_time.png' and 'comparison_mean_ob.png' generated"