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
#include "search.h"
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
short average_sorting_time(pfunc_sort metodo, int n_perms,int N, PTIME_AA ptime)
{
  int i,k;
  int** permutations=NULL;
  clock_t start,end;
  double mean_time;
  long mean_ob=0;
  int max_ob,min_ob,ob;

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
    if(ob==ERR)
    {
        for(k=0;k<n_perms;k++)
        {
          free(permutations[k]);
          }
          free(permutations);
          return ERR;
    }
    mean_ob+=ob;
    if(i==0)
    {
      max_ob=min_ob=ob;
    }
    max_ob=max_ob>ob?max_ob:ob;
    min_ob=min_ob<ob?min_ob:ob;
  }
  end=clock();

  mean_time=((double)end-start)/n_perms;

  
  /* Asignation of values to ptime */
  ptime->n_elems=n_perms;
  ptime->N=N;
  ptime->time=mean_time/CLOCKS_PER_SEC;
  ptime->average_ob=((double)mean_ob)/n_perms;
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
/**
 * @brief average_sorting_time Date:02/10/2025
 * Functions that calculatate the time, basic     
 * basic operation(max,min,mean) used by sorting  
 * algorithm  
 * @author: Shaofan Xu                             
 * Input:                                        
 * @param pfunc_sort metodo: sorting function         
 * @param int n_perms: number of permutations.           
 * @param int N: length of permutations                 
 * @param PTIME_AA ptime: structure which store all     
 * the time, basic operation used by metodo.    
 * Output:                                        
 * @return short: return 1(or OK) when everything is good 
 * and 0(or ERR) when there is errors.      
 */
short average_search_time(pfunc_search metodo, pfunc_key_generator generator,char order,int N, int n_times,PTIME_AA ptime)
{
  int i;
  PDICT pdict;
  int *permutation;
  int *keys;
  clock_t start,end;
  double mean_time;
  long mean_ob=0;
  int max_ob,min_ob,ob;
  int ppos;

  /*Error comprobation*/
  assert(metodo!=NULL);
  assert(N>0);
  assert(n_times>0);
  assert(ptime!=NULL);
  
  /* Create dictionary and verify its not NULL*/
  pdict=init_dictionary(N,order);
  if(pdict==NULL) return ERR;
  
  /* Create a permutations */
  permutation=generate_perm(N);
  if(permutation==NULL)
  {
    free_dictionary(pdict);
    return ERR;
  }
  if(massive_insertion_dictionary(pdict,permutation,N)==ERR)
  {
    free_dictionary(pdict);
    free(permutation);
    return ERR;
  }

  /*Create a table of size n_times*N*/
  keys=malloc(sizeof(keys[0])*n_times*N);
  if(keys==NULL)
  {
    free_dictionary(pdict);
    free(permutation);
    return ERR;
  }
  generator(keys,n_times*N,N);

  /* Count the time used to search the keys*/
  start=clock();

  for(i=0;i<n_times*N;i++)
  {
    ob=search_dictionary(pdict,keys[i],&ppos,metodo);
    if(ob==ERR)
    {
      free_dictionary(pdict);
      free(permutation);
      free(keys);
      return ERR;
    }
    if(i==0)
    {
      max_ob=min_ob=ob;
    }
    mean_ob+=ob;
    max_ob=max_ob<ob?ob:max_ob;
    min_ob=ob<min_ob?ob:min_ob;
  }
  end=clock();

  mean_time=((double)end-start)/(n_times*N);

  
  /* Asignation of values to ptime */
  ptime->n_elems=n_times*N;
  ptime->N=N;
  ptime->time=mean_time/CLOCKS_PER_SEC;
  ptime->average_ob=((double)mean_ob)/(n_times*N);
  ptime->min_ob=min_ob;
  ptime->max_ob=max_ob;

  /* Free all memorys */

  free(permutation);
  free_dictionary(pdict);
  free(keys);

  return OK;
}


/********************************************************************/
/* Function: save_time_table_search Date: 20/11/2025                */
/* Authors: Alejandro Zheng                                         */
/*                                                                  */
/* Function to write the measurements in a file                     */
/*                                                                  */
/* Input:                                                           */
/* char* file: the file to write measurements                       */
/* PTIME_AA ptime: structure which store all                        */
/* the time, basic operation used by metodo.                        */
/* int N: number of measurements took                               */
/* Output:                                                          */  
/* short: index to indicate if the program have runned successfully */
/********************************************************************/
short save_time_table_search(char* file, PTIME_AA time, int N)
{
  FILE *pf = NULL;
  int i;

  assert(file != NULL);
  assert(time != NULL);
  assert(N > 0);

  /*open the file*/
  pf = fopen(file,"w");
  if (pf == NULL)
  {
    return ERR;
  }

  /*print result of measurement into file*/
  fprintf(pf, "N  Time  average_ob  max_ob  min_ob \n");

  for (i = 0; i < N; i++)
  {
    fprintf(pf, "%d %.10f %.10f %d %d \n", time[i].N, time[i].time, time[i].average_ob, time[i].max_ob, time[i].min_ob);
  }

  /*close file*/
  fclose(pf);

  return OK;
}

/*********************************************************************/
/* Function: generate_search_times Date:20/11/2025                   */
/* Author: Alejandro Zheng                                           */
/*                                                                   */
/* Function that write a average of searching time,                  */
/* min,max and average of OB for one searching algoritm              */
/* in each scale of number permutations                              */
/*                                                                   */
/* Input:                                                            */
/* pfunc_search method: search function                              */
/* pfunc_key_generator generator: function to generate key           */
/* char order: order of generator                                    */
/* char* file: file where write the measurements                     */
/* int num_min: minimum scale of generator to measure                */
/* int num_max: maximum scale of generator to measure                */
/* int incr: index to grow scale of generator in each interaction    */
/* int n_times: number of search in each interaction                 */
/* Output:                                                           */
/* short: index to indicate if the program have runned successfully  */
/*********************************************************************/                              
short generate_search_times(pfunc_search method, pfunc_key_generator generator, char order, char* file, int num_min, int num_max, int incr, int n_times)
{
  PTIME_AA array_time = NULL;
  int i;
  int array_size;
  int N;
  short result;

  assert(method != NULL);
  assert(generator != NULL);
  assert(file != NULL);
  assert(num_min < num_max);

  /*Allocate memory for table of measurement*/
  array_size = (num_max - num_min) / incr + 1;
  array_time = malloc(sizeof(TIME_AA)*array_size);
  if (array_time == NULL)
  {
    return ERR;
  }
  
  /*process of measurement*/
  for (i = 0, N = num_min; N <= num_max; i++, N+=incr)
  {
    if (average_search_time(method, generator, order,N, n_times, &(array_time[i])) == ERR)
    {
      free(array_time);
      return ERR;
    }
  }

  /*save the result into a file*/
  result = save_time_table_search(file,array_time, array_size);

  /*free memory of table*/
  free(array_time);

  return result;
}


