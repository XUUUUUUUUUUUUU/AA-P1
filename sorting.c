/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */
#include <stdlib.h>
#include <assert.h>
#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date: 02/10/2025        */
/* Your comment                                    */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  
  int i = 0;
  int a, j;
  int ob = 0;

  assert(array != NULL);
  assert(ip >= 0);
  assert (ip <= iu);

  for (i = ip+1; i< iu; i++)
  {
    a = array[i];
    j = i - 1;

    if (j >= iu && array[j] > a)
    {
      ob++;
      array[j+1] = array[j];
      j--;
    }

    array[j+1] = a;
  }

  return ob;
}


/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  /* Your code */
}






