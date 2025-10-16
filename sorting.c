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

  for (i = ip+1; i<=iu; i++)
  {
    a = array[i];
    j = i - 1;


    while (j >= ip && array[j] > a)
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
  int i=iu,j;
  int ob=0; 
  int flag=1;
  int num;
  assert(array!=NULL);
  assert(ip>=0);
  assert(ip<=iu);

  while(flag==1&&i>=ip+1)
  {
    flag=0;
    for(j=ip;j<=i;j++)
    { 
      ob++;
      if(array[j]>array[j+1]){
        num=array[j];
        array[j]=array[j+1];
        array[j+1]=num;
        flag=1;
      }
    }
    i--;
  }
  return ob;
}






