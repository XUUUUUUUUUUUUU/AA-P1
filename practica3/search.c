/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Shaofan Xu, Alejandro Zheng
 * Version: 1.0
 * Date: 14-11-2025
 *
 */

#include "search.h"
#include "permutations.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>


/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

/**
 * @brief Function: init_dictionary
 *               This function inits memory for dictionary
 * @author Alejandro Zheng
 * @date 13/11/25
 * 
 * @param int size greater than 0
 * @param order order of table
 * 
 * @return pointer to dicctionary (DICT)
 *
 */

PDICT init_dictionary (int size, char order)
{
  PDICT re;

  assert(size > 0);
    
	re = malloc(1*sizeof(DICT));
  if (re == NULL)
  {
    return NULL;
  }

  re->size = size;
  re->order = order;
  re->n_data = 0;

  re->table = malloc(size*sizeof(re->table[0]));
  if (re->table == NULL)
  {
    free(re);
    return NULL;
  }

  return re;
  
}

/**
 * @brief Function: free_dictionary
 *               This function frees the allocated menory for dictionary
 * @author Shaofan Xu
 * @date 13/11/25
 * 
 * @param pdict pointer to dictionary: NOT NULL
 * 
 * @return NONE
 *
 */
void free_dictionary(PDICT pdict)
{
  assert(pdict!=NULL);
  assert(pdict->table!=NULL);
  free(pdict->table);
  free(pdict);
}

/**
 * @brief Function: insert_dictionary
 *               This function inserty key elements in table
 * @author Alejandro Zheng
 * @date 13/11/25
 * 
 * @param PDICT NON NULL pointer to dictionary
 * @param key the valid element which have to inserte in table
 * 
 * @return pointer to dicctionary
 *
 */

int insert_dictionary(PDICT pdict, int key)
{
  int ob;
  int j;

	assert(pdict != NULL);

  /*cuando los key no tiene que esta ordenado*/
  if (pdict->n_data == pdict->size)
  {
    return ERR;
  }

  pdict->table[pdict->n_data] = key;
  pdict->n_data++;

  ob = 0;

  /*cuando los key tiene que ser ordenado*/
  if (pdict->order == SORTED)
  {
    j = pdict->n_data - 2;
    
    while(j >= 0 && pdict->table[j] > key)
    {
      pdict->table[j+1] = pdict->table[j];
      j--;
      ob++;
    }
    
    pdict->table[j+1] = key;

  }

  return ob;
}

/**
 * @brief Function: massive_insertion_dictionary
 *               This function insert an array of keys in dictionary
 * @author Shaofan Xu
 * @date 13/11/25
 * 
 * @param pdict pointer to dictionary: NOT NULL
 * @param keys pointer to arrays of keys: NOT NULL
 * @param n_keys the numbers of keys : >=0
 * 
 * @return the number of basic operations does the function executed
 */
int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int obs,i;
  assert(pdict!=NULL);
  assert(pdict->table!=NULL);
  assert(keys!=NULL);
  assert(n_keys>=0);

  /*insertacion masivo de los keys*/
  obs=0;
  for(i=0;i<n_keys;i++)
  {
    obs+=insert_dictionary(pdict,keys[i]);
  }

  return obs;
}

/**
 * @brief Function: search_dictionary
 *               This function use search algoritms to find the position of key in dictionary table
 * @author Alejandro Zheng
 * @date 13/11/25
 * 
 * @param PDICT NON NULL pointer to dictionary
 * @param key the elements we have to find
 * @param ppos NON NULL pointer to indicate the position of key in dictionary table
 * @param method NON NULL pointer to function searching algoritms
 * 
 * @return pointer to dicctionary
 *
 */
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  int ob;

	assert(pdict != NULL);
  assert(method != NULL);

  /*Usa un algoritmo de búsqueda para busca un key en un diccionario*/
  if (pdict->n_data == 0)
  {
    *ppos = NOT_FOUND;
    return 0;
  }
  ob = method(pdict->table,0,pdict->n_data-1, key, ppos);

  return ob;
}


/* Search functions of the Dictionary ADT */

/**
 * @brief Function: bin_search
 *               This function use binary_search to find an element in the table
 * @author Shaofan Xu
 * @date 13/11/25
 * 
 * @param table pointer to table which we want to search: NOT NULL
 * @param F the position of first element in the table: >=0, <=total element in the table
 * @param L the position of last element in the table: >=F
 * @param ppos pointer to the position of key in the table which we have to store in it: NOT NULL
 * 
 * @return the number of basic operations does the function executed 
 */
int bin_search(int *table,int F,int L,int key, int *ppos)
{ 
  int mid,left,right,obs;

  assert(table!=NULL);
  assert(F>=0);
  assert(L>=F);
  assert(ppos!=NULL);
  
  left=F;
  right=L;
  obs=0;

  /*Busqueda binaria*/
  while(left<=right)
  {
    mid=(left+right)/2;
    obs++;
    if(table[mid]==key) /*Operación Basica*/
    {
      *ppos=mid;
      return obs;
    }else if(table[mid]<key)
    {
      left=mid+1;
    }else{
      right=mid-1;
    }
  }
  *ppos=NOT_FOUND;
  return obs;
}

/**
 * @brief Function: lin_search
 *               This function use lineal_search to find an element in the table
 * @author Alejandro Zheng
 * @date 13/11/25
 * 
 * @param table pointer to table which we want to search: NOT NULL
 * @param F the position of first element in the table: >=0, <=total element in the table
 * @param L the position of last element in the table: >=F
 * @param ppos pointer to the position of key in the table which we have to store in it: NOT NULL
 * 
 * @return the number of basic operations does the function executed 
 */
int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int ob;
  int i;
	assert(table != NULL);
  assert(F<=L);
  assert(ppos != NULL);

  ob = 0;

  /*Busqueda lineal*/
  for (i = F; i <=L; i++)
  {
    ob++;
    if (table[i] == key) /*Operación basica*/
    {
      *ppos = i;
      return ob;
    }

  }

  *ppos = NOT_FOUND;

  return ob;
}

/**
 * @brief Function: lin_auto_search
 *               This function use linel_auto_search to find an element in the table
 * @author Shaofan Xu
 * @date 13/11/25
 * 
 * @param table pointer to table which we want to search: NOT NULL
 * @param F the position of first element in the table: >=0, <=total element in the table
 * @param L the position of last element in the table: >=F
 * @param ppos pointer to the position of key in the table which we have to store in it: NOT NULL
 * 
 * @return the number of basic operations does the function executed
 */
int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
  int i,obs;
  assert(table!=NULL);
  assert(F>=0);
  assert(L>=F);
  assert(ppos!=NULL);

  obs=0;

  /*Es una busqueda lineal pero con la modificacion de que el elemento buscado se intercambia la posicion con su anterio*/
  /*Entonces, si un key buscamos más veces, su posicion va ser más delante*/
  for(i=F;i<=L;i++)
  {
    obs++;
    if(table[i]==key) /*Operación basica*/
    {
      if(i>F)
      {
        /*intercambia la posicion de key encontrado con su anterio*/
        swap(&table[i],&table[i-1]);
        *ppos=i-1;
      }else{
        *ppos=i;
      }
      return obs;
    }
  }
  *ppos=NOT_FOUND;
  return obs;
}


