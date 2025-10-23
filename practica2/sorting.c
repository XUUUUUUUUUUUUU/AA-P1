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


/**********************************************************/
/* Function: mergesort     Date: 23/10/2025               */
/* Authors: Alejandro Zheng                               */
/*                                                        */
/* Function that sorts a given array using mergesort      */
/* Input:                                                 */
/* int *tabla: Pointer to the array which have be sorted  */
/* int ip: index of first element of array                */
/* int iu: index of last element of array                 */
/* Output:                                                */
/* int: number of basic operations that function executed */
/**********************************************************/
int mergesort(int* tabla, int ip, int iu)
{
  int imedio = 0;
  int ob1,ob2,ob3;
  
  /*asserting conditions*/
  assert(tabla != NULL);
  assert(ip < iu);

  /*table with one element*/
  if (ip == iu) return OK;
  
  /*calculate the middle*/
  imedio = (ip-iu) / 2;
  
  /*dividing the table*/
  ob1 = mergesort(tabla, ip, imedio);
  ob2 = mergesort(tabla, imedio + 1, iu);

  /*combine the tabl*/
  ob3 = merge(tabla, ip, iu, imedio);

  assert(ob1 != -1);
  assert(ob2 != -1);
  assert(ob3 != -1);
  
  return ob1+ob2+ob3;
}

/**************************************************************/
/* Function: merge     Date: 23/10/2025                       */
/* Authors: Alejandro Zheng                                   */
/*                                                            */
/* Complement function for merge sorts that combines elements */
/*                                                            */
/* int *tabla: Pointer to the array which have be sorted      */
/* int ip: index of first element of array                    */
/* int iu: index of last element of array                     */
/* int imedio: index of middle elements of array              */
/* Output:                                                    */
/* int: number of basic operations that function executed     */
/**************************************************************/
int merge(int* tabla, int ip, int iu, int imedio)
{

  int* aux_table = NULL;
  int size;
  int i,j,k;
  int ob;

  /*asserting contidions*/
  assert(tabla != NULL);
  assert(ip < iu);
  assert(ip < imedio);
  assert(iu > imedio);

  /*Calculate the size of table*/
  size = (iu - ip) + 1; 

  /*malloc an auxiliar table */
  aux_table = malloc(sizeof(int)*size);
  if(aux_table == NULL)
  {
    return -1;
  }
  
  i = ip;
  j = imedio + 1;
  k = ip;
  
  /*process of combining*/
  while( i <= imedio && j <= iu)
  {
    if (tabla[i] < tabla[j])
    {
      aux_table[k] = tabla[i];
      ob++;
      i++;
      k++;
      
    }else
    {
      aux_table[k] = tabla[j];
      ob++;
      j++;
      k++;
    }
  }

  /*copy the rest elements of aux_table*/
  if (i > imedio)
  {
    for(;j <= iu;j++,k++)
    {
      aux_table[k] = tabla[j];
      ob++;
    }
  }
  
  /*copy the rest elements of aux_table*/
  if (j > iu)
  {
    for(;i <= imedio;i++,k++)
    {
      aux_table[k] = tabla[i];
      ob++;
    }
  }
  
  /*copy the aux_table to table*/
  for (i = ip, j = 0; i <= iu; i++, j++)
  {
    tabla[i] = aux_table[j];
  }

  /*free aux_table*/
  free(aux_table);
  
  return ob;
  
}
/**********************************************************/
/* Function: median       Date: 23/10/2025                */
/* Authors: Shaofan Xu.                                   */
/*                                                        */
/* Function that calculate the pivote we have to chose    */
/* (in this case first element of table)                  */
/* Input:                                                 */
/* int *tabla: Pointer to the table which have be divided */
/* int ip: index of first element of table                */
/* int iu: index of last element of table                 */
/* int *pos: pointer which store the position of pivote   */
/* element                                                */
/* Output:                                                */
/* 0: OK, -1: ERR                                         */
/**********************************************************/
int median(int *tabla, int ip, int iu,int *pos)
{
  assert(tabla!=NULL);
  assert(ip>=0);
  assert(ip<=iu);
  assert(pos!=NULL);

  *pos=ip;
  return OK;
}

/**********************************************************/
/* Function: partition    Date: 23/10/2025                */
/* Authors: Shaofan Xu.                                   */
/*                                                        */
/* Function that divide a given table in two.             */
/* Input:                                                 */
/* int *tabla: Pointer to the table which have be divided */
/* int ip: index of first element of table                */
/* int iu: index of last element of table                 */
/* int *pos: pointer which store the position of pivote   */
/* element                                                */
/* Output:                                                */
/* ERR in case of error, or number of OBs that function   */
/* has excuted in otherwise                               */
/**********************************************************/
int partition(int* tabla, int ip, int iu,int *pos)
{
  int element,i,obs=0;
  
  assert(tabla!=NULL);
  assert(ip>=0);
  assert(ip<=iu);
  assert(pos!=NULL);
  
  if(median(tabla,ip,iu,pos)==ERR)return ERR;
  element=tabla[*pos];

  swap(tabla[ip],tabla[*pos]);
  *pos=ip;

  for(i=ip+1;i<=iu;i++)
  {
    if(tabla[i]<element)
    {
      obs++;
      *pos++;
      swap(tabla[i],tabla[*pos]);
    }
  }
  swap(tabla[ip],tabla[*pos]);
  return obs;
}


/**********************************************************/
/* Function: quicksort       Date: 23/10/2025             */
/* Authors: Shaofan Xu.                                   */
/*                                                        */
/* Function that sort a given table                       */
/* (in this case first element of table)                  */
/* Input:                                                 */
/* int *tabla: Pointer to the table which have be divided */
/* int ip: index of first element of table                */
/* int iu: index of last element of table                 */
/* Output:                                                */
/* ERR in case of error, and number of OBs in otherwise   */
/**********************************************************/
int quicksort(int* tabla, int ip, int iu)
{
  int mid=0;
  int *position=NULL;
  assert(tabla!=NULL);
  assert(ip>=0);
  assert(ip<=iu);

  /*Base case*/
  if(ip==iu)return 0;
  else{
    position=malloc(sizeof(position[0]));
    if(position==NULL) return ERR;

    if((mid=partition(tabla,ip,iu,position))==ERR)
    {
      free(position);
      return ERR;
    }
    if(ip<mid-1)quicksort(tabla,ip,iu);
    if(mid+1<iu)quicksort(tabla,ip,iu);
  }
  return OK;
}
