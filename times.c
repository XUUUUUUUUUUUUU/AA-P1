/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Shaofan Xu, Alejandro Zheng
 * Version: 1.0
 * Fecha: 2/10/2025
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
/* Autor: Shaofan Xu                               */
/*                                                 */
/* Functions that calculatate the time, basic      */
/* basic operation(max,min,mean) used by sorting   */
/* algorithm                                       */
/*                                                 */
/* Input:                                          */
/* pfunc_sort metodo: sorting function             */
/* int n_perms: number of permutations.            */
/* int N: length of permutations                   */
/* PTIME_AA ptime: structure which store all       */
/* the time, basic operation used by metodo.       */
/* Output:                                         */
/* short: return 1(or OK) when everything is good  */
/* and 0(or ERR) when there is errors.             */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int i;
  int** permutations=NULL;
  clock_t start,end;
  double mean_time;
  int mean_ob=0,max_ob,min_ob,ob;

  /*Error comprobation*/
  assert(metodo!=NULL);
  assert(n_perms>0);
  assert(N>0);
  assert(ptime!=NULL);
  
  /*Generate n_perms permutations of size N and verify that is not NULL*/
  permutations=generate_permutations(n_perms,N);
  if(permutations==NULL) return ERR;
  
  /* Count the time used to order*/
  start=clock();

  for(i=0;i<n_perms;i++)
  { 
    ob=metodo(permutations[i],0,N-1);
    mean_ob+=ob;
    if(i==0)
    {
      max_ob=min_ob=ob;
    }
    max_ob=max_ob>ob?max_ob:ob;
    min_ob=min_ob<ob?min_ob:ob;
  }
  end=clock();

  mean_time=(double)(end-start)/n_perms;

  
  /* Asignation of values to ptime */
  ptime->n_elems=n_perms;
  ptime->N=N;
  ptime->time=mean_time/CLOCKS_PER_SEC;
  ptime->average_ob=(double)mean_ob/n_perms;
  ptime->min_ob=min_ob;
  ptime->max_ob=max_ob;

  /* Free all memorys */

  for(i=0;i<n_perms;i++)
  {
    free(permutations[i]);
  }
  free(permutations);

    return OK;
}

/*********************************************************************/
/* Function: generate_sorting_times Date:16/10/2025                  */
/* Author: Alejandro Zheng                                           */
/*                                                                   */
/* Function that write a average of sorting time,                    */
/* min,max and average of OB for one sorting algoritm                */
/* in each scale of number permutations                              */
/*                                                                   */
/* Input:                                                            */
/* pfunc_sort method: sorting function                               */
/* char* file: file where write the measurements                     */
/* int num_min: minimum scale of permutation to measure              */
/* int num_max: maximum scale of permutation to measure              */
/* int incr: index to grow scale of permutation in each interaction  */
/* int n_perms: number of permutations                               */
/* Output:                                                           */
/* short: index to indicate if the program have runned successfully  */
/*********************************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  
  PTIME_AA array_time = NULL;
  int i;
  int n_times;
  int N;
  short result;
  
  assert(method != NULL);
  assert(file != NULL);
  assert(num_min >0);
  assert(num_min < num_max);

  n_times = (num_max -num_min) / incr + 1;

  array_time = malloc(sizeof(TIME_AA)*n_times);
  if(array_time == NULL)
  {
    return ERR;
  }
  
  for(i=0,N = num_min; N <= num_max&&i<n_times; i++, N+= incr)
  {
    if (average_sorting_time(method, n_perms,N, &(array_time[i])) == ERR)
    {
      free(array_time);
      return ERR;
    }
  }

  result = save_time_table(file, array_time, n_times);

  free(array_time);

  return result;

}

/********************************************************************/
/* Function: save_time_table Date: 16/10/2025                       */
/* Authors: Alejandro Zheng                                         */
/*                                                                  */
/* Function to write the measurement in a file                      */
/*                                                                  */
/* Input:                                                           */
/* char* file: the file to write measurement                        */
/* PTIME_AA ptime: structure which store all                        */
/* the time, basic operation used by metodo.                        */
/* int n_times: number of measurement took                          */
/* Output:                                                          */  
/* short: index to indicate if the program have runned successfully */
/********************************************************************/
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
    fprintf(pf, "%d %f %f %d %d \n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  }

  fclose(pf);

  return OK;
}


