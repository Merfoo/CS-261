/*	dynArr.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	
	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* newDynArr(int cap)
{
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{
	/* FIXME: You will write this function */

    /* Make sure v, v->data aren't null and a valid capacity was given */
    assert((v && v->data) && newCap >= 0);

    /* If the new capacity is the same as the current, do nothing */
    if(v->capacity == newCap)
        return;

    /* Create new dynamic array with new capacity size */
    TYPE* newData = (TYPE*)malloc(sizeof(TYPE) * newCap);
    assert(newData);

    /* Copy over the data from the current dynamic array to new one */
    int i = 0; 

    for(i = 0; i < v->size && i < newCap; i++)
        newData[i] = v->data[i];

    /* Delete current dynamic data array and set it to the new one */
    freeDynArr(v);
    v->data = newData;
    v->size = i;
    v->capacity = newCap;
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	/* FIXME: You will write this function */

    /* Check v and v->data aren't null */
    assert(v && v->data);

    /* Check if there is room for new data, if not, expand */
    if(v->size >= v->capacity)
    {
        if(v->capacity < 1)
            v->capacity = 1;

        _dynArrSetCapacity(v, v->capacity * 2);
    }

    /* Add data to end of array, increase size variable */
    v->data[v->size] = val;
    v->size++;
}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/
TYPE getDynArr(DynArr *v, int pos)
{
	/* FIXME: You will write this function */
    
    /* Check v and v->data aren't null, 0 <= pos < size */
    assert((v && v->data) && (pos >= 0 && pos < v->size));
 
    /* Return value at given index in array */
	return v->data[pos];
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	/* FIXME: You will write this function */

    /* Check v and v->data aren't null, 0 <= pos < v->size */
    assert((v && v->data) && (pos >= 0 && pos < v->size));
    v->data[pos] = val;
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	/* FIXME: You will write this function */

    /* Check v and v->data aren't null */
    assert(v && v->data);

    /* Check both i and j are >= 0 and < v->size */
    assert((i >= 0 && i < v->size) && (j >= 0 && j < v->size));

    /* Swap variables using temp variable */
    TYPE temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	/* FIXME: You will write this function */

    /* Check v and v->data aren't null, 0 <= idx < v->size */
    assert((v && v->data) && (idx >= 0 && idx < v->size));

    /* Shift over alll elements after idx left one, decrease size */
    int i = idx;

    for(i = idx; i < v->size - 1; i++)
        v->data[i] = v->data[i + 1];

    v->size--;
}

/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	/* FIXME: You will write this function */

    /* Check v and v->data aren't null */
    assert(v && v->data);

    /* Return true if size == 0 */
	return v->size == 0;
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	/* FIXME: You will write this function */

    /* Add element to end of array */
    addDynArr(v, val);
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	/* FIXME: You will write this function */

    /* Check if v and v->data aren't null and size > 0 */
    assert((v && v->data) && v->size > 0);

    /* Return last element of array */
	return v->data[v->size - 1];
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	/* FIXME: You will write this function */

    /* Check if v is null, size > 0 */
    assert(v && v->size > 0);

    /* Decrement size by 1, thus removing the last element */
    v->size--;
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	/* FIXME: You will write this function */

    /* Check if v and v->data aren't null */
    assert(v && v->data);

    /* Loop through array checking if val exists inside of it */
    int i = 0;

    for(i = 0; i < v->size; i++)
        if(v->data[i] == val)
            return i;

	return -1;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	int index = containsDynArr(v,val);
	removeAtDynArr(v,index);	
}