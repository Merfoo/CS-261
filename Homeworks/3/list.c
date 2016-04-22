#include "listbag.h"
#include "type.h"
#include <assert.h>
#include <stdlib.h>

/*
	function to initialize the list, set the sentinels and set the size
	param l the list
	pre: l is not null
	post: l size is 0
*/

void initList (struct list *l) {
	/* FIX ME*/
}


/*
	_addLink
	Funtion to add a value v to the list before the link l
	param: l the list
	param: lnk the  link to add before
	param: v the value to add
	pre: l is not null
	pre: lnk is not null
	post: l is not empty
*/

void _addLink(struct list *l, struct DLink *lnk, TYPE v)
{
	/* FIX ME*/
}


/*
	addFrontList
	Function to add a value to the front of the list, can use _addLink()
	param: l the list
	param: e the element to be added
	pre: l is not null
	post: l is not empty, increased size by 1
*/

void addFrontList(struct list *l, TYPE e)
{
	/* FIX ME*/
}

/*
	addBackList
	Function to add a value to the back of the list, can use _addlink()
	param: l the list
	pre: l is not null
	post: l is not empty
*/

void addBackList(struct list *l, TYPE e) {
	/* FIX ME*/
}

/*
	frontList
	function to return the element in the front of the  list
	param: l the list
	pre: l is not null
	pre: l is not empty
	post: none
*/

TYPE frontList (struct list *l) {
	/* FIX ME*/
}

/*
	backList
	function to return the element in the back of the  list
	param: l the list
	pre: l is not null
	pre: l is not empty
	post: l is not empty
*/

TYPE backList(struct list *l)
{
	/* FIX ME*/
}

/*
	_removeLink
	Function to remove a given link
	param: l the list
	param: lnk the linke to be removed
	pre: l is not null
	pre: lnk is not null
	post: l size is reduced by 1
*/

void _removeLink(struct list *l, struct DLink *lnk)
{
	/* FIX ME*/
}

/*
	removeFrontList
	Function to remove element from front of list, can use _removelink()
	param: l the list
	pre:l is not null
	pre: l is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct list *l) {
	/* FIX ME*/
}

/*
	removeBackList
	Function to remove element from back of list, can use _removelink()
	param: l the list
	pre: l is not null
	pre:l is not empty
	post: size reduced by 1
*/

void removeBackList(struct list *l)
{
	/* FIX ME*/
}

/*
	isEmptyList
	param: q the list
	pre: q is not null
	post: none
*/

int isEmptyList(struct list *l) {
	/* FIX ME*/
}



/* Recursive implementation of contains()
 Pre: current is not null
 Post: 1 if found, 0 otherwise
 */
int _contains_recursive(struct DLink* current, TYPE e){
	/* FIX ME*/
}

/* Wrapper function for contains
 Pre: l is not null
 Post: 1 if found, 0 otherwise
 */
int listContains (struct list *l, TYPE e) {
	assert(!isEmptyList(l));
	return _contains_recursive(l->head, e);
}

/* Recursive implementation of remove()*/
void _remove_recursive(struct DLink* current, TYPE e, int* sz){
	/* FIX ME*/
}
/* Wrapper for remove()*/
void listRemove (struct list *l, TYPE e) {
	/* FIX ME*/
}


void freeList(struct list *q)
{
    /* FIX ME*/
}



