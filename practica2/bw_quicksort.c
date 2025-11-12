/**************************************************/
/* Programa: best_worst_time       Date:09/11/25  */
/* Authors: Shaofan Xu                            */
/*                                                */
/* Program that calculate used time in best case  */
/* and worst case of QuickSort using first pivote */
/*                                                */
/* Input: Command Line                            */
/* -num_min: lowest number of table elements      */
/* -num_max: highest number of table elements     */
/* -incr: increment\n                             */
/* -numP: number of permutations to average       */
/* -quicksort_outputFile: Output file name of     */
/* quicksort                                      */                    
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

void free_worst_arr(int *worst_case_array)
{
    if (worst_case_array != NULL)
        free(worst_case_array);
}
void free_best_arr(int *best_case_array)
{
    if (best_case_array != NULL)
        free(best_case_array);
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
int *worst_case_array(int N)
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
void build_best_first_pivot(const int *sorted, int l, int r, int *out, int *pos){
    int m;   
    if (l > r) return;
    m = l + (r - l) / 2;     
    out[(*pos)++] = sorted[m];    
    build_best_first_pivot(sorted, l, m - 1, out, pos); 
    build_best_first_pivot(sorted, m + 1, r, out, pos); 
}

int *best_case_array(int N){
    int i,pos;
    int *src;
    int *dst;
    if (N <= 0) return NULL;
    src = malloc(sizeof(int)*N);
    dst = malloc(sizeof(int)*N);
    if (!src || !dst){ free(src); free(dst); return NULL; }

    for (i = 0; i < N; i++) src[i] = i + 1; 
    pos = 0;
    build_best_first_pivot(src, 0, N - 1, dst, &pos);

    free(src);
    return dst;
}

short run_test(pfunc_sort metodo, const char *file_name,
                      int num_min, int num_max, int incr, int n_perms)
{
    int i, k, n_times, N;
    int *best_pat = NULL, *worst_pat = NULL, *tmp = NULL;
    clock_t start, end;
    double **time_table = NULL;
    FILE *file = NULL;

    n_times = (num_max - num_min) / incr + 1;

    time_table = malloc(sizeof(*time_table)*2);
    if (!time_table) return ERR;
    for (i = 0; i < 2; i++){
        time_table[i] = malloc(sizeof(**time_table)*n_times);
        if (!time_table[i]){ free_time_table(time_table); return ERR; }
    }

    file = fopen(file_name, "w");
    if (!file){ free_time_table(time_table); return ERR; }
    fprintf(file, "N bc_time wc_time\n");

    for (i = 0, N = num_min; i < n_times && N <= num_max; i++, N += incr){
        /* --- Best case pattern for size N --- */
        best_pat = best_case_array(N);
        if (!best_pat){ fclose(file); free_time_table(time_table); return ERR; }

        /* --- Worst case pattern for size N --- */
        worst_pat = worst_case_array(N);
        if (!worst_pat){ free(best_pat); fclose(file); free_time_table(time_table); return ERR; }

        tmp = malloc(sizeof(int)*N);
        if (!tmp){ free(best_pat); free(worst_pat); fclose(file); free_time_table(time_table); return ERR; }

        /* ---- measure best ---- */
        start = clock();
        for (k = 0; k < n_perms; k++){
            memcpy(tmp, best_pat, sizeof(int)*N);
            if (metodo(tmp, 0, N - 1) == ERR){
                free(tmp); free(best_pat); free(worst_pat); fclose(file); free_time_table(time_table);
                return ERR;
            }
        }
        end = clock();
        time_table[0][i] = ((double)(end - start) / CLOCKS_PER_SEC) / (double)n_perms;

        /* ---- measure worst ---- */
        start = clock();
        for (k = 0; k < n_perms; k++){
            memcpy(tmp, worst_pat, sizeof(int)*N);
            if (metodo(tmp, 0, N - 1) == ERR){
                free(tmp); free(best_pat); free(worst_pat); fclose(file); free_time_table(time_table);
                return ERR;
            }
        }
        end = clock();
        time_table[1][i] = ((double)(end - start) / CLOCKS_PER_SEC) / (double)n_perms;

        free(tmp); tmp = NULL;
        free(best_pat); best_pat = NULL;
        free(worst_pat); worst_pat = NULL;

        fprintf(file, "%d %f %f\n", N, time_table[0][i], time_table[1][i]);
    }

    free_time_table(time_table);
    fclose(file);
    return OK;
}


int main(int argc, char **argv)
{
    int i, num_min = 0, num_max = 0, incr = 0, n_perms = 0;
    char quickSort_filename[256];

    srand(time(NULL));

    if (argc != 11)
    {
        fprintf(stderr, "Error in input parameters:\n\n");
        fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
        fprintf(stderr, "\t\t -numP <int> -quicksort_outputFile <string> \n");
        fprintf(stderr, "Donde:\n");
        fprintf(stderr, "-num_min: lowest number of table elements\n");
        fprintf(stderr, "-num_max: highest number of table elements\n");
        fprintf(stderr, "-incr: increment\n");
        fprintf(stderr, "-numP: number of permutations to average\n");
        exit(-1);
    }

    printf("Practice number 2\n");
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
        else if (strcmp(argv[i], "-quicksort_outputFile") == 0)
        {
            strcpy(quickSort_filename, argv[++i]);
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
    assert(incr>0);

    /*Test the best and worst case of quickSort*/
    if (run_test(quicksort, quickSort_filename, num_min, num_max, incr, n_perms) == ERR)
    {
        return ERR;
    }
    return 0;
}