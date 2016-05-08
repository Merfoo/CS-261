#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skipList.h"
#include <time.h>	


/* ************************************************************************
Main Function
 ************************************************************************ */
/* Test function:
 param: no parameters
 pre:	no parameres
 post: prints out the contents of the skip list */

void test(){
	int i;
	
	/*  FIX ME */
	
	/*  Initialize the skip list */
	
	/*  Add to the skip list  M = 20 random integers in [0,100] */
	
	/*  Print out the contents of the skip list in the breadth-first order, starting from top. 
	 While printing the elements, move to a new line every time you reach the end of one level, 
	 and move down to the lower level of the skip list. 
	 For example, the print out of a skip list with 5 elements should look like
	 
	 7
	 7 14 29
	 3 7 9 14 20
	 
	 */
	
	/* Develop test cases for evaluating the following functions:  
	 int containsSkipList(struct skipList *slst, TYPE e) 
	 int removeSkipList(struct skipList *slst, TYPE e)
	 */
	
}


/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* Coin toss function:
 param: 	no parameters
 pre:	no parameres
 post: output is a random intiger number in {0,1} */
int flipSkipLink(void)
{
	/*  FIX ME */	
}

/* Move to the right as long as the next element is smaller than the input value:
 param: 	current -- pointer to a place in the list from where we need to slide to the right
 param:	e --  input value
 pre:	current is not NULL
 post: returns one link before the link that contains the input value e */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	
	/* FIX ME */
}


/* Create a new skip link for a value
	param: e	 -- the value to create a link for
	param: nextLnk	 -- the new link's next should point to nextLnk
	param: downLnk -- the new link's down should point to downLnk
	pre:	none
	post:	a link to store the value */
struct skipLink* newSkipLink(TYPE e, struct skipLink * nextLnk, struct skipLink* downLnk) {
	struct skipLink * tmp = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(tmp != 0);
	tmp->value = e;
	tmp->next = nextLnk;
	tmp->down = downLnk;
	return tmp;
}


/* Add a new skip link recursively
 param: current -- pointer to a place in the list where the new element should be inserted
 param: e	 -- the value to create a link for
 pre:	current is not NULL
 post: a link to store the value */
struct skipLink* skipLinkAdd(struct skipLink * current, TYPE e) {
	struct skipLink *newLink, *downLink;
	newLink = 0;
	if (current->down == 0) {
		newLink = newSkipLink(e, current->next, 0);
		current->next = newLink;
	}
	else {
		downLink = skipLinkAdd(slideRightSkipList(current->down, e), e);
		if (downLink != 0 && flipSkipLink()) {
			newLink = newSkipLink(e, current->next, downLink);
			current->next = newLink;
		}
	}
	return newLink;
}


/* ************************************************************************
Public Functions
 ************************************************************************ */

/* Initialize skip list:
 param:  slst -- pointer to the skip list
 pre:	slst is not null
 post: the sentinels are allocated, the pointers are set, and the list size equals zero */
void initSkipList (struct skipList *slst) 
{
	/* FIX ME*/
}

/* Checks if an element is in the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be checked
 pre:	slst is not null
 post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e)
{
	/* FIX ME*/
}


/* Remove an element from the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be removed
 pre:	slst is not null
 post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e)
{
	/* FIX ME*/
}




/* Add a new element to the skip list:
	param: slst -- pointer to the skip list
	param: e -- element to be added
	pre:	slst is not null
	post:	the new element is added to the lowest list and randomly to higher-level lists */
void addSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *downLink, *newLink;
	downLink = skipLinkAdd(slideRightSkipList(slst->topSentinel,e),e);
	
	/* FIX ME*/

}


/* Find the number of elements in the skip list:
 param: slst -- pointer to the skip list
 pre:	slst is not null
 post: the number of elements */
int sizeSkipList(struct skipList *slst)
{
	
	/* FIX ME*/	
}

/* Print the links in the skip list:
	param: slst -- pointer to the skip list
	pre:	slst is not null and slst is not empty
	post: the links in the skip list are printed breadth-first, top-down */
void printSkipList(struct skipList *slst)
{
	/* FIX ME*/
}

/* Merge two skip lists, by adding elements of skip list 2 to skip list 1 
   that are not already contained in skip list 1. 
   The function is also supposed to remove the entire skip list 2 from the memory.
   param: slst1 -- pointer to the skip list 1
   param: slst2 -- pointer to the skip list 2
   pre: slst1 and slst2 are not null, and skip list 1 and skip list 2 are not empty
   post: slst1 points to the merger skip list,  slst2 is null*/
void mergeSkipList(struct skipList *slst1, struct skipList *slst2)
{

	/* FIX ME*/
	
}
