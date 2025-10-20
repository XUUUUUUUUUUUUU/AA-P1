/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Shaofan Xu, Alejandro Zheng
 * Version: 1.1
 * Fecha: 25-09-2025
 *
 */


#include "permutations.h"

#include <stdlib.h>
#include <assert.h>

void swap(int *a,int *b)
{
  int number;
  number=*a;
  *a=*b;
  *b=number;
}


/***************************************************/
/* Function: random_num Date:28/9/25               */
/* Authors: Shaofan Xu                             */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  /* Return equiprobable random numbers */
  return inf+(sup-inf+1)*(double)(rand()/((double)RAND_MAX+1.0));
}

/***************************************************/
/* Function: generate_perm Date:28/9/25            */
/* Authors: Shaofan Xu                             */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int *perm=NULL;
  int i;

  /* Verified that N its not zero or negative number*/
  assert(N>0);

  perm=malloc(N*sizeof(perm[0]));
  if(perm==NULL) return NULL;

  for(i=0;i<N;i++) perm[i]= i+1;

  for(i=0;i<N;i++)
  {
    /* Switch with the element at random position */
    swap(&perm[i],&perm[random_num(i,N-1)]);
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:28/9/25    */
/* Authors:Shaofan Xu                              */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{ 
  
  int **perms=NULL;
  int i,j;
  
  /* Error comprobation*/
  assert(n_perms>0);
  assert(N>0);
  
  /*Reserve memory for array*/
  perms=malloc(n_perms*sizeof(perms[0]));
  if(perms==NULL) return NULL;

  for(i=0;i<n_perms;i++)
  {
    /* Generate permutation*/
    perms[i]=generate_perm(N);
    if(perms[i]==NULL)
    {
      for(j=0;j<i;j++)
      {
        free(perms[j]);
      }
      free(perms);
    }
  }

  return perms;
}
