set terminal pngcairo size 800,600 font "Arial,10"


#1. Comparacion de binSearch y linSearch(Not Sorted): ntimes=1 using uniform_key_generator
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

#2.Comparacion de binSearch y linAutoSearch(Not Sorted): ntimes=1 using potencial_key_generator
    
set output 'binSearch_linAutoSearch_ntimes1.png'
set title "binSearch-linAutoSearch - Tiempo Medio"
     #ajustar con una funcion constante
    g(x)=c
fit g(x) 'linAutoSearch_NotSortedPkg_ntimes1.log' using 1:2 via c
plot 'binSearch_SortedPkg_ntimes1.log' using 1:2 with linespoints title 'binSearch',\
    'linAutoSearch_NotSortedPkg_ntimes1.log' using 1:2 with linespoints title 'linAutoSearch',\
    g(x) with lines lw 2 title sprintf("%.2e", c)

#3.Comparacion de binSearch y linAutoSearch(Not Sorted): ntimes=100 using potencial_key_generator
    
set output 'binSearch_linAutoSearch_ntimes100.png'
set title "binSearch-linAutoSearch - Tiempo Medio"
     #ajustar con una funcion constante
    h(x)=d
fit h(x) 'linAutoSearch_NotSortedPkg_ntimes100.log' using 1:2 via d
plot 'binSearch_SortedPkg_ntimes100.log' using 1:2 with linespoints title 'binSearch',\
    'linAutoSearch_NotSortedPkg_ntimes100.log' using 1:2 with linespoints title 'linAutoSearch',\
    h(x) with lines lw 2 title sprintf("%.2e", d)

#4.Comparacion de binSearch y linAutoSearch(Not Sorted): ntimes=10000 using potencial_key_generator
    
set output 'binSearch_linAutoSearch_ntimes10000.png'
set title "binSearch-linAutoSearch - Tiempo Medio"
     #ajustar con una funcion constante
    l(x)=f
fit l(x) 'linAutoSearch_NotSortedPkg_ntimes10000.log' using 1:2 via f
plot 'binSearch_SortedPkg_ntimes10000.log' using 1:2 with linespoints title 'binSearch',\
    'linAutoSearch_NotSortedPkg_ntimes10000.log' using 1:2 with linespoints title 'linAutoSearch',\
    l(x) with lines lw 2 title sprintf("%.2e", f)