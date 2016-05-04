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
    
    /* Check if l is null */
    assert(l);

    /* Initialize head and tail links in list */
    l->head = (struct DLink*)malloc(sizeof(struct DLink));
    l->tail = (struct DLink*)malloc(sizeof(struct DLink));
    assert(l->head && l->tail);

    l->head->value = 0;
    l->head->next = l->tail;
    l->head->prev = 0;

    l->tail->value = 0;
    l->tail->next = 0;
    l->tail->prev = l->head;

    /* Init size to 0 */
    l->size = 0;
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

    /* Check if l, lnk is null */
    assert(l && lnk);

    /* Create link value v */
    struct DLink* newLnk = (struct DLink*)malloc(sizeof(struct DLink));
    assert(newLnk);

    newLnk->value = v;
    newLnk->next = lnk;
    newLnk->prev = lnk->prev;

    /* Link lnk to newLnk */
    lnk->prev = newLnk;

    /* Update links around newLnk */
    newLnk->prev->next = newLnk;

    /* Incremement size by 1 */
    l->size++;
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

    /* Check if l is null */
    assert(l);

    /* Add new link to front of list with value e */
    _addLink(l, l->head->next, e);
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

    /* Check if l is null */
    assert(l);

    /* Add new link to back of the list with value e */
    _addLink(l, l->tail, e);
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

    /* Check if l is null and is l empty */
    assert(l && !isEmptyList(l));

    /* Return the first links value */
    return l->head->next->value;
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

    /* Check if l is null and is l empty */
    assert(l && !isEmptyList(l));

    /* Return the last links value */
    return l->tail->prev->value;
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

    /* Check if l and lnk is null */
    assert(l && lnk);

    /* Connect links around lnk to eachother */
    lnk->prev->next = lnk->next;
    lnk->next->prev = lnk->prev;

    /* Free lnk */
    free(lnk);

    /* Decrease list size by 1 */
    l->size--;
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

    /* Check if l is null and l is empty */
    assert(l && !isEmptyList(l));

    /* Remove first link */
    _removeLink(l, l->head->next);
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

    /* Check if l is null and l is empty */
    assert(l && !isEmptyList(l));

    /* Remove last link */
    _removeLink(l, l->tail->prev);
}

/*
	isEmptyList
	param: q the list
	pre: q is not null
	post: none
*/

int isEmptyList(struct list *l) {
	/* FIX ME*/

    /* Check if l is null */
    assert(l);

    /* Return true (1) is size == 0, false (0) otherwise */
    return l->size == 0;
}



/* Recursive implementation of contains()
 Pre: current is not null
 Post: 1 if found, 0 otherwise
 */
int _contains_recursive(struct DLink* current, TYPE e){
	/* FIX ME*/

    /* Check if current is null */
    assert(current);

    /* If current->prev is null we're at the head, skip to the
    *  next since head doesn't contain any value
    */
    if(!current->prev)
        current = current->next;

    /* If current->next is null we've come across the tail,
    *  thus the list doesn't contain the value e, return false (0)
    */
    if(!current->next)
        return 0;
    
    /* If the current->value is == to e then return true(1) */
    if(current->value == e)
        return 1;

    /* Else call this function again with the next 
    *  link and return the result */
    return _contains_recursive(current->next, e);
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
    
    /* Create tmp variable for next link */
    struct DLink* next = current->next;

    /* If the next is null, we're at the tail and at the end of the list */
    if(!next)
        return;

    /* If link value == e, remove it from the list */
    if(current->value == e)
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        (*sz)--;
    }
    
    /* Continue recursively calling with next link as starting point */
    _remove_recursive(next, e, sz);
}

/* Wrapper for remove()*/
void listRemove (struct list *l, TYPE e) {
	/* FIX ME*/

    /* Check if l is null */
    assert(l);

    /* If the list is empty just return */
    if(isEmptyList(l))
        return;

    /* Call _remove_recursive with the entire list */
    _remove_recursive(l->head->next, e, &l->size);
}


void freeList(struct list *q)
{
    /* FIX ME*/

    /* Check if q is null */
    assert(q);

    /* Create link for iterating over list */
    struct DLink* curLnk = q->head;

    /* Iterate over list, deleting each link, including head/tail */
    while(curLnk)
    {
        struct DLink* nextLnk = curLnk->next;
        free(curLnk);
        curLnk = nextLnk;
    }

    free(q);
}
