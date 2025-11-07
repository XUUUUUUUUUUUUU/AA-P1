/**************************************************/
/* Programa: bw_mergesort       Date:06/11/25     */
/* Authors: Alejandro Zheng                       */
/*                                                */
/* Program that calculate used time in best case  */
/* and worst case of Mergesort                    */
/*                                                */
/* Input: Command Line                            */
/* -num_min: lowest number of table elements      */
/* -num_max: highest number of table elements     */
/* -incr: increment\n                             */
/* -numP: number of permutations to average       */
/* -insertSort_outputFile: Output file name of    */
/* insertSort                                     */           
/* Output: -1 in case of error                    */
/*  0 otherwise                                   */
/**************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "sorting.h"
#include "times.h"

/*Create the array for best case*/
int *best_mergesort_arry(int N)
{
    int i;
    int *array;

    array = malloc(sizeof(array[0]) *N);
    if(array == NULL)
    {
        return NULL;
    }
    for (i = 0; i < N ; i++)
    {
        array[i] = i+1;
    }

    return array;

}

/*Free the array for best case in mergesort*/
void free_best_mergesort_arry(int * best_mergesort_arry)
{
    if (best_mergesort_arry != NULL)
        free(best_mergesort_arry);
}

/*Free the array for worst case in mergesorts*/
void free_worst_mergesort_arry(int ** worst_mergesort_arry, int n_perms)
{
    int i;
    if(worst_mergesort_arry != NULL)
    {
        for (i = 0; i< n_perms; i++)
        {
            if(worst_mergesort_arry[i]!= NULL)
            {
                free(worst_mergesort_arry[i]);
            }
        }
        free(worst_mergesort_arry);

    }
}

/*Create the array for worst case*/
int **worst_mergesort_arry(int n_perms,int N)
{
    int i,j;
    int **array;

    array = malloc(sizeof(array[0])*n_perms);
    if (array == NULL)
    {
        return NULL;
    }

    for (i = 0; i<n_perms; i++)
    {
        array[i] = malloc(sizeof(array[i][0]) * N);
        if(array[i] == NULL)
        {
            free_worst_mergesort_arry(array, i);
            return NULL;
        }
        for (j = 0; j < N; j++)
        {
            array[i][j]= N -i;
        }
    }

    return array;
}


/*Free the time table*/
void free_time_table(double **time_table)
{
    int i;
    if (time_table != NULL)
    {
        for (i = 0; i < 2; i++)
        {
            if (time_table[i] != NULL)
                free(time_table[i]);
        }

        free(time_table);
    }
}

/*running test for measurement*/
short run_test(pfunc_sort metodo, char *file_name, int num_min, int num_max, int incr, int n_perms)
{
    int n_times, k, N;
    clock_t start, end;
    double **time_table; 
    int *best_arry;
    int **worst_arry;
    FILE *fp;
    int i;

    n_times = (num_max - num_min)/ incr + 1;

    /*Create the best array for mergesort*/
    time_table = malloc(sizeof(time_table[0])* 2);
    if (time_table == NULL)
    {
        return ERR;
    }

    for (i = 0; i < 2; i++)
    {
        time_table[i] = malloc(sizeof(time_table[i][0]) * n_times);
        if (time_table[i] == NULL)
        {
            free_time_table(time_table);
            return ERR;
        }
    }


    /*Create best case array for mergesort*/
    best_arry = best_mergesort_arry(num_max);
    if (best_arry == NULL)
    {
        free_time_table(time_table);
        return ERR;
    }

    
    for (i = 0, N = num_min; i < n_times && N <= num_max; i++, N += incr)
    {
        
        /*measure the best case for mergesort*/
        start = clock();
        for (k = 0; k < n_perms; k++)
        {
            if (metodo(best_arry,0, N-1) == ERR)
            {
                free_best_mergesort_arry(best_arry);
                free_time_table(time_table);
                return ERR;
            }
        }
        end = clock();
        time_table[0][i]= (double)(end - start)/CLOCKS_PER_SEC;
        time_table[0][i]/=(double)n_perms;
    
        /*Create worst case array for mergesort*/
        worst_arry = worst_mergesort_arry(n_perms, N);
        if(worst_arry == NULL)
        {
            free_best_mergesort_arry(best_arry);
            free_time_table(time_table);
            return ERR;
        }

        /*measure the worst case for mergesort*/
        start = clock();
        for (k = 0; k<n_perms; k++)
        {
            if (metodo(worst_arry[k],0, N-1) == ERR)
            {
                free_best_mergesort_arry(best_arry);
                free_time_table(time_table);
                free_worst_mergesort_arry(worst_arry, n_perms);
                return ERR;
            }
        }
        end = clock();
        time_table[1][i] = (double)(end - start)/CLOCKS_PER_SEC;
        time_table[1][i] /= (double)n_perms;
        free_worst_mergesort_arry(worst_arry,n_perms);
    }

    /*writing measurements to file*/
    fp = fopen(file_name, "w");
    if(fp == NULL)
    {
        free_time_table(time_table);
        free_best_mergesort_arry(best_arry);
        return ERR;
    }

    fprintf(fp, "N bc_time wc_time\n");

    for (i =0, N =num_min; i< n_times && N <= num_max; i++, N += incr)
    {
        fprintf(fp, "%d %f %f\n", N, time_table[0][i], time_table[1][i]);
    }

    free_time_table(time_table);
    free_best_mergesort_arry(best_arry);
    fclose(fp);
    return OK;
}

int main(int argc, char **argv)
{
    int i, num_min = 0,num_max = 0,n_perms = 0,incr =0;
    char filename[512];

    srand(time(NULL));

    if (argc != 11) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: lowest number of table elements\n");
    fprintf(stderr, "-num_max: highest number of table elements\n");
    fprintf(stderr, "-incr: increment\n");
    fprintf(stderr, "-numP: number of permutations to average\n");
    fprintf(stderr, "-outputFile: Output file name\n");
    exit(-1);
  }

    printf("Practice number 2, section 6\n");
    printf("Done by: Shaofan Xu y Alejandro Zheng\n");
    printf("Grupo: 120/127\n");
  

      /* check command line */
    for(i = 1; i < argc ; i++) {
        if (strcmp(argv[i], "-num_min") == 0) {
        num_min = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-num_max") == 0) {
        num_max = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-incr") == 0) {
        incr = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-numP") == 0) {
        n_perms = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-outputFile") == 0) {
        strcpy(filename, argv[++i]);
        } else {
        fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
        }
    }

    /*ERROR comprobation*/
    assert(n_perms>0);
    assert(num_min>0);
    assert(num_max>0);
    assert(num_min<=num_max);

    if(run_test(mergesort,filename,num_min,num_max,incr,n_perms) == ERR)
    {
        return ERR;
    }

    return 0;
}
