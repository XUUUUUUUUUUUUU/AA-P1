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
     #ajustar con una funcion lineal
     t(x)=g*x+h
fit f(x) 'binSearch_Sorted_ntimes1.log' using 1:2 via a,b
fit t(x) 'linSearch_NotSorted_ntimes1.log' using 1:2 via g,h
plot 'binSearch_Sorted_ntimes1.log' using 1:2 with linespoints title 'binSearch',\
    'linSearch_NotSorted_ntimes1.log' using 1:2 with linespoints title 'linSearch',\
    f(x) with lines lw 2 title sprintf("%.2e*log(n)+%.2e", a,b),\
    t(x) with lines lw 2 title sprintf("%.2e*x+%.2e",g,h)

#2.Comparacion de binSearch y linAutoSearch(Not Sorted): ntimes=1 using potencial_key_generator
    
set output 'binSearch_linAutoSearch_ntimes1.png'
set title "binSearch-linAutoSearch - Tiempo Medio"
     #ajustar con una funcion constante
    g(x)=c
    #ajustar con una funcion logaritmica
    k(x)=i*log(x)+j
fit g(x) 'linAutoSearch_NotSortedPkg_ntimes1.log' using 1:2 via c
fit k(x) 'binSearch_SortedPkg_ntimes1.log' using 1:2 via i,j
plot 'binSearch_SortedPkg_ntimes1.log' using 1:2 with linespoints title 'binSearch',\
    'linAutoSearch_NotSortedPkg_ntimes1.log' using 1:2 with linespoints title 'linAutoSearch',\
    g(x) with lines lw 2 title sprintf("%.2e", c),\
    k(x) with lines lw 2 title sprintf("%.2e*log(x)+%.2e",i,j)

#3.Comparacion de binSearch y linAutoSearch(Not Sorted): ntimes=100 using potencial_key_generator
    
set output 'binSearch_linAutoSearch_ntimes100.png'
set title "binSearch-linAutoSearch - Tiempo Medio"
     #ajustar con una funcion constante
    h(x)=d
     #ajustar con una funcion logaritmica
     p(x)=a*log(x)+b
fit h(x) 'linAutoSearch_NotSortedPkg_ntimes100.log' using 1:2 via d
fit p(x) 'binSearch_SortedPkg_ntimes100.log' using 1:2 via a,b

plot 'binSearch_SortedPkg_ntimes100.log' using 1:2 with linespoints title 'binSearch',\
    'linAutoSearch_NotSortedPkg_ntimes100.log' using 1:2 with linespoints title 'linAutoSearch',\
    h(x) with lines lw 2 title sprintf("%.2e", d),\
    p(x) with lines lw 2 title sprintf("%.2e*log(x)+%.2e",a,b)

#4.Comparacion de binSearch y linAutoSearch(Not Sorted): ntimes=10000 using potencial_key_generator
    
set output 'binSearch_linAutoSearch_ntimes10000.png'
set title "binSearch-linAutoSearch - Tiempo Medio"
     #ajustar con una funcion constante
    l(x)=a
     #ajustar con una funcion logaritmica
    g(x)=c*log(x)+d
fit l(x) 'linAutoSearch_NotSortedPkg_ntimes10000.log' using 1:2 via a
fit g(x) 'binSearch_SortedPkg_ntimes10000.log' using 1:2 via c,d

plot 'binSearch_SortedPkg_ntimes10000.log' using 1:2 with linespoints title 'binSearch',\
    'linAutoSearch_NotSortedPkg_ntimes10000.log' using 1:2 with linespoints title 'linAutoSearch',\
    l(x) with lines lw 2 title sprintf("%.2e", a),\
    g(x) with lines lw 2 title sprintf("%.2e*log(x)+%.2e", c,d)


#5. Caso mejor y peor de obs de binSearch 

set output 'binSearch_Sorted_Best_Worst_Case.png' 
set ylabel "Obs"

    #ajuste logaritmica
    min_ob(x)=a*log(x)+b
    max_ob(x)=c*log(x)+d
fit min_ob(x) 'binSearch_Sorted_ntimes1.log' using 1:5 via a,b
fit max_ob(x) 'binSearch_Sorted_ntimes1.log' using 1:4 via c,d

plot 'binSearch_Sorted_ntimes1.log' using 1:4 with linespoints title 'binSearch_MaxObs',\
    'binSearch_Sorted_ntimes1.log' using 1:5 with linespoints title 'binSearch_MinObs',\
    min_ob(x) with lines lw 2 title sprintf("%.2e*log(x)+%.2e", a,b),\
    max_ob(x) with lines lw 2 title sprintf("%.2e*log(x)+%.2e", c,d)

#6.Caso mejor y peor de obs de linSearch 

set output 'linSearch_NotSorted_Best_Worst_Case.png' 
set ylabel "Obs"

    #ajuste logaritmica
    min_ob(x)=a*x
    max_ob(x)=c*x
fit min_ob(x) 'linSearch_NotSorted_ntimes1.log' using 1:5 via a
fit max_ob(x) 'linSearch_NotSorted_ntimes1.log' using 1:4 via c

plot 'linSearch_NotSorted_ntimes1.log' using 1:4 with linespoints title 'linSearch_MaxObs',\
    'linSearch_NotSorted_ntimes1.log' using 1:5 with linespoints title 'linSearch_MinObs',\
    min_ob(x) with lines lw 2 title sprintf("%.2e*x", a),\
    max_ob(x) with lines lw 2 title sprintf("%.2e*x", c)

#7. todos los n_times juntos
set output 'todos juntos.png'
set ylabel 'Tiempo'
plot 'binSearch_SortedPkg_ntimes10000.log' using 1:2 with linespoints title 'binSearch ntimes10000',\
    'linAutoSearch_NotSortedPkg_ntimes10000.log' using 1:2 with linespoints title 'linAutoSearch ntimes10000',\
    'binSearch_SortedPkg_ntimes1.log' using 1:2 with linespoints title 'binSearch ntimes1',\
    'linAutoSearch_NotSortedPkg_ntimes1.log' using 1:2 with linespoints title 'linAutoSearch ntimes1', \
    'binSearch_SortedPkg_ntimes100.log' using 1:2 with linespoints title 'binSearch ntimes100',\
    'linAutoSearch_NotSortedPkg_ntimes100.log' using 1:2 with linespoints title 'linAutoSearch ntimes100'


#7. todos los n_times juntos
set output 'todos juntos obs.png'
set ylabel 'Obs'
plot 'binSearch_SortedPkg_ntimes10000.log' using 1:3 with linespoints title 'binSearch ntimes10000',\
    'linAutoSearch_NotSortedPkg_ntimes10000.log' using 1:3 with linespoints title 'linAutoSearch ntimes10000',\
    'binSearch_SortedPkg_ntimes1.log' using 1:3 with linespoints title 'binSearch ntimes1',\
    'linAutoSearch_NotSortedPkg_ntimes1.log' using 1:3 with linespoints title 'linAutoSearch ntimes1', \
    'binSearch_SortedPkg_ntimes100.log' using 1:3 with linespoints title 'binSearch ntimes100',\
    'linAutoSearch_NotSortedPkg_ntimes100.log' using 1:3 with linespoints title 'linAutoSearch ntimes100'