#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall -O3
EXE = exercise4 exercise5 

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

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 5

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 10 -num_max 10000 -incr 10 -numP 10 -outputFile exercise5.log

valgrind_e4_test:
	@echo Running exercise4 with valgrind
	@valgrind --leak-check=full -s ./exercise4 -size 1

valgrind_e5_test:
	@echo Running exercise5 with valgrind
	@valgrind --leak-check=full -s ./exercise5 -num_min 10 -num_max 100 -incr 10 -numP 1000 -outputFile exercise5.log

valgrind_e6_test:
	@echo Running exercise5 with valgrind
	@valgrind --leak-check=full -s ./exercise6 -num_min 10 -num_max 100 -incr 10 -numP 1000 -outputFile exercise6.log

