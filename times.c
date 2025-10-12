/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


/***************************************************/
/* Function: average_sorting_time Date:02/10/2025  */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  /* Precondition */
  
  int i;
  int** permutations=NULL;
  clock_t start,end;
  double mean_time;
  int *basic_operation=NULL,mean_bo=0;

  assert(metodo!=NULL);
  assert(n_perms>0);
  assert(N>0);
  assert(ptime!=NULL);
  
  permutations=generate_permutations(n_perms,N);
  if(permutations==NULL) return ERR;
  
  basic_operation=malloc(n_perms*sizeof(basic_operation[0]));
  if(basic_operation==NULL)
  {
    for(i=0;i<n_perms;i++)
    {
      free(permutations[i]);
    }
    free(permutations);
    return ERR;
  }
  
  start=clock();

  for(i=0;i<n_perms;i++)
  { 
    basic_operation[i]=metodo(permutations[i],0,N);
    mean_bo+=basic_operation[i];
  }
  end=clock();
  mean_time=(double)(end-start)/n_perms;

  /* Order the array of basic operation */
   metodo(basic_operation,0,n_perms);

  
  /* Asignation of values to ptime */
  ptime->n_elems=n_perms;
  ptime->N=N;
  ptime->time=mean_time/CLOCKS_PER_SEC;
  ptime->average_ob=mean_bo/n_perms;
  ptime->min_ob=basic_operation[0];
  ptime->max_ob=basic_operation[n_perms-1];

  /* Free all memorys */
  free(basic_operation);

  for(i=0;i<n_perms;i++)
  {
    free(permutations[i]);
  }
  free(permutations);

    return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  
  PTIME_AA *array_time = NULL;
  int i;
  int n_times;
  int num;
  short re;
  
  assert(method != NULL);
  assert(file != NULL);
  assert(num_min >0);
  assert(num_min < num_max);

  n_times = (num_max -num_min) / incr + 1;

  array_time = malloc(sizeof(PTIME_AA)*n_times);
  if(array_time == NULL)
  {
    return ERR;
  }
  
  for(num = num_min, i=0; num <= num_max; i++, num+= incr)
  {
    if (average_sorting_time(method, n_perms,num, array_time[i]) == ERR)
    {
      free(array_time);

      return ERR;
    }
  }

  re = save_time_table(file, array_time, i);

  free(array_time);

  return re;

}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *pf = NULL;
  int i;

  assert(file != NULL);
  assert(ptime != NULL);
  assert(n_times > 0);

  pf = fopen(file,"w");
  if (pf == NULL)
  {
    return ERR;
  }

  fprintf(pf, "N  Time  average_ob  max_ob  min_ob \n");

  for (i = 0; i < n_times; i++)
  {
    fprintf(pf, "%d %f %f %d %d \n", ptime->N, ptime->time, ptime->average_ob, ptime->max_ob, ptime->min_ob);
  }

  fclose(pf);

  return OK;

}


