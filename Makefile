#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall -O3
EXE = exercise1 exercise2 exercise3 exercise4 exercise5 exercise6 best_worst_time

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

exercise1_test:
	@echo Running exercise1
	@./exercise1 -limInf 1 -limSup 2 -numN 10

exercise2_test:
	@echo Running exercise2
	@./exercise2 -size 5 -numP 5

exercise3_test:
	@echo Running exercise3
	@./exercise3 -size 5 -numP 5

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 5

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 10 -num_max 1000 -incr 10 -numP 1000 -outputFile exercise5.log

exercise6_test:
	@echo Running exercise6
	@./exercise6 -num_min 10 -num_max 1000 -incr 10 -numP 1000 -outputFile exercise6.log

best_worst_time_test:
	@echo Running best_worst_time
	@./best_worst_time -num_min 10 -num_max 1000 -incr 10 -insertsort_outputFile insertsort.log -bubblesort_outputFile bubblesort.log

valgrind_e1_test:
	@echo Running exercise1 with valgrind
	@valgrind --leak-check=full -s ./exercise1 -limInf 1 -limSup 5 -numN 10

valgrind_e2_test:
	@echo Running exercise2 with valgrind
	@valgrind --leak-check=full -s ./exercise2 -size 1 -numP 5

valgrind_e3_test:
	@echo Running exercise3 with valgrind
	@valgrind --leak-check=full -s ./exercise3 -size 1 -numP 5

valgrind_e4_test:
	@echo Running exercise4 with valgrind
	@valgrind --leak-check=full -s ./exercise4 -size 1

valgrind_e5_test:
	@echo Running exercise5 with valgrind
	@valgrind --leak-check=full -s ./exercise5 -num_min 10 -num_max 1000 -incr 10 -numP 1000 -outputFile exercise5.log

valgrind_e6_test:
	@echo Running exercise5 with valgrind
	@valgrind --leak-check=full -s ./exercise6 -num_min 10 -num_max 1000 -incr 10 -numP 1000 -outputFile exercise6.log
