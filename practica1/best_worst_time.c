/**************************************************/
/* Programa: best_worst_time       Date:20/10/25  */
/* Authors: Shaofan Xu                            */
/*                                                */
/* Program that calculate used time in best case  */
/* and worst case of InsertSort and BubbleSort    */
/*                                                */
/* Input: Command Line                            */
/* -num_min: lowest number of table elements      */
/* -num_max: highest number of table elements     */
/* -incr: increment\n                             */
/* -numP: number of permutations to average       */
/* -insertSort_outputFile: Output file name of    */
/* insertSort                                     */
/* -bubbleSort_outputFile: Output file name of    */
/* bubbleSort                                     */
/* Output: -1 in case of error                    */
/*  0 otherwise                                   */
/**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "sorting.h"
#include "times.h"

void free_best_arr(int *best_case_array)
{
    if (best_case_array != NULL)
        free(best_case_array);
}
void free_worst_arr(int **worst_case_array, int n_perms)
{
    int i;
    if (worst_case_array != NULL)
    {
        for (i = 0; i < n_perms; i++)
        {
            if (worst_case_array[i] != NULL)
                free(worst_case_array[i]);
        }
        free(worst_case_array);
    }
}
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
int *best_case_array(int N)
{
    int i;
    int *array = NULL;
    /*Error comprobation*/
    assert(N > 0);

    array = malloc(sizeof(array[0]) * N);
    if (array == NULL)
        return NULL;

    for (i = 0; i < N; i++)
    {
        array[i] = i + 1;
    }
    return array;
}
int **worst_case_array(int n_perms, int N)
{
    int i, j;
    int **array = NULL;
    /*Error comprobation*/
    assert(N > 0);

    array = malloc(sizeof(array[0]) * n_perms);
    if (array == NULL)
        return NULL;

    for (i = 0; i < n_perms; i++)
    {
        array[i] = malloc(sizeof(array[i][0]) * N);
        if (array[i] == NULL)
        {
            free_worst_arr(array, i);
            return NULL;
        }
        for (j = 0; j < N; j++)
        {
            array[i][j] = N - j;
        }
    }
    return array;
}

short run_test(pfunc_sort metodo, char *file_name, int num_min, int num_max, int incr, int n_perms)
{
    int i, k, n_times, N;
    int *best_case_arr = NULL, **worst_case_arr = NULL;
    clock_t start, end;
    double **time_table = NULL;
    FILE *file = NULL;

    n_times = (num_max - num_min) / incr + 1;

    /*Allocate memory for array which store best time and worst time sorting algorithm*/
    time_table = malloc(sizeof(time_table[0]) * 2);
    if (time_table == NULL)
        return ERR;

    for (i = 0; i < 2; i++)
    {
        time_table[i] = malloc(sizeof(time_table[i][0]) * n_times);
        if (time_table[i] == NULL)
        {
            free_time_table(time_table);
            return ERR;
        }
    }

    /* Reserve memory for best case array */
    best_case_arr = best_case_array(num_max);
    if (best_case_arr == NULL)
    {
        free_time_table(time_table);
        return ERR;
    }

    for (i = 0, N = num_min; i < n_times && N <= num_max; i++, N += incr)
    {
        start = clock();
        for (k = 0; k < n_perms; k++)
        {
            if (metodo(best_case_arr, 0, N - 1) == ERR)
            {
                free_best_arr(best_case_arr);
                free_time_table(time_table);
                return ERR;
            }
        }
        end = clock();
        time_table[0][i] = (double)(end - start) / CLOCKS_PER_SEC;
        time_table[0][i] /= (double)n_perms;

        /* Reserve memory for the worst case*/
        worst_case_arr = worst_case_array(n_perms, N);
        if (worst_case_arr == NULL)
        {
            free_best_arr(best_case_arr);
            free_time_table(time_table);
            return ERR;
        }
        start = clock();
        for (k = 0; k < n_perms; k++)
        {
            if (metodo(worst_case_arr[k], 0, N - 1) == ERR)
            {

                free_best_arr(best_case_arr);
                free_worst_arr(worst_case_arr, n_perms);
                free_time_table(time_table);
                return ERR;
            }
        }
        free_worst_arr(worst_case_arr, n_perms);
        end = clock();
        time_table[1][i] = (double)(end - start) / CLOCKS_PER_SEC;
        time_table[1][i] /= (double)n_perms;
    }

    file = fopen(file_name, "w");

    if (file == NULL)
    {
        free_time_table(time_table);
        free_best_arr(best_case_arr);
        return ERR;
    }
    fprintf(file, "N bc_time wc_time\n");

    /*Print datas*/
    for (i = 0, N = num_min; i < n_times && N <= num_max; i++, N += incr)
    {
        fprintf(file, "%d %f %f\n", N, time_table[0][i], time_table[1][i]);
    }
    free_time_table(time_table);
    free_best_arr(best_case_arr);
    fclose(file);
    return OK;
}

int main(int argc, char **argv)
{
    int i, num_min = 0, num_max = 0, incr = 0, n_perms = 0;
    char bubbleSort_filename[256], insertSort_filename[256];

    srand(time(NULL));

    if (argc != 13)
    {
        fprintf(stderr, "Error in input parameters:\n\n");
        fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
        fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
        fprintf(stderr, "Donde:\n");
        fprintf(stderr, "-num_min: lowest number of table elements\n");
        fprintf(stderr, "-num_max: highest number of table elements\n");
        fprintf(stderr, "-incr: increment\n");
        fprintf(stderr, "-numP: number of permutations to average\n");
        fprintf(stderr, "-insertsort_outputFile: InsertSort Output file name\n");
        fprintf(stderr, "-bubblesort_outputFile: BubbleSort Output file name\n");
        exit(-1);
    }

    printf("Practice number 1, section 6b\n");
    printf("Done by: Shaofan Xu y Alejandro Zheng\n");
    printf("Grupo: 120/127\n");

    /* check command line */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-num_min") == 0)
        {
            num_min = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-num_max") == 0)
        {
            num_max = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-incr") == 0)
        {
            incr = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-numP") == 0)
        {
            n_perms = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-insertsort_outputFile") == 0)
        {
            strcpy(insertSort_filename, argv[++i]);
        }
        else if (strcmp(argv[i], "-bubblesort_outputFile") == 0)
        {
            strcpy(bubbleSort_filename, argv[++i]);
        }
        else
        {
            fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
        }
    }

    /*ERROR comprobation*/
    assert(n_perms>0);
    assert(num_min>0);
    assert(num_max>0);
    assert(num_min<=num_max);

    /*Test the best and worst case of InsertSort*/
    if (run_test(InsertSort, insertSort_filename, num_min, num_max, incr, n_perms) == ERR)
    {
        return ERR;
    }

    /*Test the best and worst case of BubbleSort*/
    if (run_test(BubbleSort, bubbleSort_filename, num_min, num_max, incr, n_perms) == ERR)
    {
        return ERR;
    }
    return 0;
}