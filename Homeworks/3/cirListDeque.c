#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cirListDeque.h"

/* internal functions interface */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);

/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void initCirListDeque (struct cirListDeque *q) 
{
	/* FIX ME*/
    
    /* Check if q is null */
    assert(q);

    /* Initialize q->Sentinel */
    q->Sentinel = _createLink(0);
    q->Sentinel->prev = 0;
    q->Sentinel->next = 0;

    /* Set q->size to 0 */
    q->size = 0;
}

/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* FIX ME*/

    /* Create DLink pointer with TYPE val */
    struct DLink* link = (struct DLink*)malloc(sizeof(struct DLink));
    assert(link);
    
    link->value = val;

    return link;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	newLnk	pointer to the new link to add after the existing link
	pre:	q is not null
	pre: 	lnk and newLnk are not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk)
{
	/* FIX ME*/

    /* Check if q, lnk, newLnk is null */
    assert(q && lnk && newLnk);

    /* Set newLnk->prev and newLnk->next */
    newLnk->prev = lnk;
    newLnk->next = lnk->next;

    /* Update lnk->next to newLnk */
    lnk->next = newLnk;

    /* Update newLnk->next-> to newLnk */
    newLnk->next->prev = newLnk;

    /* Increment size of q */
    q->size++;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* If no links, add first link that connects to itself for circularity */
    if(isEmptyCirListDeque(q))
    {
        struct DLink* lnk = _createLink(val);
        lnk->prev = lnk;
        lnk->next = lnk;

        q->Sentinel->next = lnk;
        q->size++;
    }

    /* Add link to back of list, aka prev of front link */
    else
        _addLinkAfter(q, q->Sentinel->next->prev, _createLink(val));
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Just add link to the back and change the q->Sentinel next */
    addBackCirListDeque(q, val);
    q->Sentinel->next = q->Sentinel->next->prev;
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	/* FIX ME*/
    
    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Check if q is empty */
    assert(!isEmptyCirListDeque(q));

    /* Return value of first link */
    return q->Sentinel->next->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Check if q is empty */
    assert(!isEmptyCirListDeque(q));

    /* Return value of last link */
    return q->Sentinel->next->prev->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	pre:	lnk is in the deque 
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel, lnk is null */
    assert(q && q->Sentinel && lnk);

    /* Check if q is empty */
    assert(!isEmptyCirListDeque(q));

    /* If only one link, free it and set q->Sentinel to null */
    if(q->size == 1)
    {
        free(q->Sentinel->next);
        q->Sentinel->next = 0;
    }

    /* Update the links connections around the removed lnk */
    else
    {
        lnk->prev->next = lnk->next;
        lnk->next->prev = lnk->prev;

        /* Update q->Sentinel->next if removed lnk was the q->Sentinel->next */
        if(q->Sentinel->next == lnk)
            q->Sentinel->next = lnk->next;

        free(lnk);
    }

    q->size--;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	/* FIX ME*/

    /* Check if q, q->Sentinel is not null */
    assert(q && q->Sentinel);

    /* Check if q is empty */
    assert(!isEmptyCirListDeque(q));

    /* Remove first link */
    _removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Check if q is empty */
    assert(!isEmptyCirListDeque(q));

    /* Remove last link */
    _removeLink(q, q->Sentinel->next->prev);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including backSentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Loop over all links, freeing them */
    struct DLink* curLnk = q->Sentinel->next;
    
    while(q->size > 0 && curLnk)
    {   
        struct DLink* nextLnk = curLnk->next;
        free(curLnk);
        curLnk = nextLnk;
        q->size--;
    }

    /* Free sentinel and list deque */
    free(q->Sentinel);
    free(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	/* FIX ME*/
    
    /* Check if q is null */
    assert(q);

    return q->size == 0;
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Loop over all lnks, printing their values */
    struct DLink* curLnk = q->Sentinel->next;
    int lnkCount = 0;

    while(lnkCount < q->size && curLnk)
    {
        printf("Link %d value: %f\n", lnkCount + 1, curLnk->value);
        curLnk = curLnk->next;
        lnkCount++;
    }
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	/* FIX ME*/

    /* Check if q, q->Sentinel is null */
    assert(q && q->Sentinel);

    /* Loop over all links, switching the prev and next variables */
    struct DLink* curLnk = q->Sentinel->next;
    int lnkCount = 0;

    while(lnkCount < q->size && curLnk)
    {
        struct DLink* tmpNext = curLnk->next;
        curLnk->next = curLnk->prev;
        curLnk->prev = tmpNext;
        curLnk = tmpNext;
        lnkCount++;
    }

    /* Update q->Sentinel->next to new front link */
    q->Sentinel->next = q->Sentinel->next->next;
}
