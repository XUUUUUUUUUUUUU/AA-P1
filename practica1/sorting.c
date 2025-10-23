/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Shaofan Xu, Alejandro Zheng
 * Version: 1.0
 * Fecha: 2-10-2025
 *
 */
#include <stdlib.h>
#include <assert.h>
#include "sorting.h"

/**********************************************************/
/* Function: InsertSort    Date: 16/10/2025               */
/* Authors: Alejandro Zheng                               */
/*                                                        */
/* Function that sorts a given array                      */
/* Input:                                                 */
/* int *array: Pointer to the array which have be sorted  */
/* int ip: index of first element of array                */
/* int iu: index of last element of array                 */
/* Output:                                                */
/* int: number of basic operations that function executed */
/**********************************************************/
int InsertSort(int* array, int ip, int iu)
{
  
  int i = 0,j;
  int num;
  int ob = 0;

  /*Error comprobation*/
  assert(array != NULL);
  assert(ip >= 0);
  assert (ip <= iu);

  /*Order the array*/
  for (i = ip+1; i<=iu; i++)
  {
    num = array[i];
    j = i - 1;


    while (j >= ip && array[j] > num)
    {
      ob++; 
      array[j+1] = array[j];
      j--;
    }

    array[j+1] = num;
  }

  return ob;
}


/***************************************************/
/* Function: BubbleSort    Date:9/10/25            */
/* Autor: Shaofan Xu                               */
/*                                                 */
/* Functions that sort a given array               */
/*                                                 */
/* Input:                                          */
/* int* array: Pointer to tha array we want to sort*/
/* int ip: index of first element of array         */
/* int iu: index of last element of array          */
/* Output:                                         */
/* int: number of basic operation does the function*/
/* executed                                        */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int i=iu,j;
  int ob=0; 
  int flag=1;
  int num;

  /*Error comprobation*/
  assert(array!=NULL);
  assert(ip>=0);
  assert(ip<=iu);

  while(flag==1&&i>=ip+1)
  {
    flag=0;
    for(j=ip;j<i;j++)
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






