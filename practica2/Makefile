#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic 
CFLAGS = -Wall -O3 
EXE = exercise4_mergesort exercise4_quicksort exercise5_mergesort exercise5_quicksort bw_mergesort bw_quicksort

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

%: %.o %.o
	$(CC) -o $@ $^
	
permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

exercise4_mergesort_test:
	@echo Running exercise4_mergesort
	@./exercise4_mergesort -size 5

exercise4_quicksort_test:
	@echo Running exercise4_quicksort
	@./exercise4_quicksort -size 5

exercise5_mergesort_test:
	@echo Running exercise5_mergesort
	@./exercise5_mergesort -num_min 10 -num_max 10000 -incr 10 -numP 10 -outputFile exercise5_mergesort_median_avg.log

exercise5_quicksort_test:
	@echo Running exercise5_quicksort
	@./exercise5_quicksort -num_min 10 -num_max 100000 -incr 10 -numP 10 -outputFile exercise5_quicksort_median_stat.log

bw_quicksort_test:
	@echo Running bw_quicksort
	@./bw_quicksort -num_min 10 -num_max 100000 -incr 10 -numP 10 -quicksort_outputFile bw_quicksort.log

valgrind_e4_mergesort:
	@echo Running exercise4_mergesort with valgrind
	@valgrind --leak-check=full -s ./exercise4_mergesort -size 10

valgrind_e4_quicksort:
	@echo Running exercise4_quicksort with valgrind
	@valgrind --leak-check=full -s ./exercise4_quicksort -size 10

valgrind_e5_mergesort:
	@echo Running exercise5_mergesort with valgrind
	@valgrind --leak-check=full -s ./exercise5_mergesort -num_min 10 -num_max 100 -incr 10 -numP 1000 -outputFile exercise5_mergesort.log

valgrind_e5_quicksort:
	@echo Running exercise5_quicksort with valgrind
	@valgrind --leak-check=full -s ./exercise5_quicksort -num_min 10 -num_max 100 -incr 10 -numP 1000 -outputFile exercise5_quicksort.log

exercise6_mergesort:
	@echo Running bw_mergesort
	@./bw_mergesort -num_min 10 -num_max 10000 -incr 10 -numP 10 -outputFile bw_mergesort.log

valgrind_e6_mergesort:
	@echo Running bw_mergesort with valgrind
	@valgrind --leak-check=full -s ./bw_mergesort -num_min 10 -num_max 100 -incr 10 -numP 1000 -outputFile bw_mergesort.log