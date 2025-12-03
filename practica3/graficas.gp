set terminal pngcairo size 800,600 font "Arial,10"


#1. Comparacion de binSearch y linSearch(Not Sorted): ntimes=1
set output 'binSearch_linSearch_ntimes1.png'
set title "binSearch-linSearch - Tiempo Medio"
set xlabel "Tamaño array(N)"
set ylabel "Tiempo(s)"

set grid
set key top left
     #ajustar con una funcion logaritmica
    f(x)=a*log(x)+b
fit f(x) 'binSearch_Sorted_ntimes1.log' using 1:2 via a,b
plot 'binSearch_Sorted_ntimes1.log' using 1:2 with linespoints title 'binSearch',\
    'linSearch_NotSorted_ntimes1.log' using 1:2 with linespoints title 'linSearch',\
    f(x) with lines lw 2 title sprintf("%.2e*log(n)+%.2e", a,b)
    
