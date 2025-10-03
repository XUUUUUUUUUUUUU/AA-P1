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
  
  PTIME_AA time = NULL;
  
  assert(method != NULL);
  assert(file != NULL);
  assert(num_min >0);
  assert(num_min < num_max);
  assert(num_min <= n_perms);
  assert(num_max >= n_perms);

  /*Malloc PTIME_AA*/
  time = malloc(1*sizeof(TIME_AA));
  if (time == NULL)
  {
    return ERR;
  }
  
  

  
  
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}


