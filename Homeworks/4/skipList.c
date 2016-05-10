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

    /* Seed psuedo-random number generator */
    srand(time(NULL));

	int i;
	
	/*  FIX ME */
	
	/*  Initialize the skip list */
    struct skipList* list = (struct skipList*)malloc(sizeof(struct skipList));
    assert(list);
    initSkipList(list);

    struct skipList* listB = (struct skipList*)malloc(sizeof(struct skipList));
    assert(listB);
    initSkipList(listB);

    addSkipList(listB, 10.0);
    addSkipList(listB, 11.0);
    addSkipList(listB, 12.0);
    addSkipList(listB, 13.0);

	
	/*  Add to the skip list  M = 20 random integers in [0,100] */
    i = 0;
    TYPE val;
    while(i++ < 1)
    {
        val = (double)(rand() % 101);
        printf("Val: %f\n", val);
    	addSkipList(list, val);
    }

    addSkipList(list, 1.0);
    addSkipList(list, 3.0);
    addSkipList(list, 7.0);
    addSkipList(list, 6.0);
    addSkipList(list, 3.0);

	/*  Print out the contents of the skip list in the breadth-first order, starting from top. 
	 While printing the elements, move to a new line every time you reach the end of one level, 
	 and move down to the lower level of the skip list. 
	 For example, the print out of a skip list with 5 elements should look like
	 
	 7
	 7 14 29
	 3 7 9 14 20
	 
	 */
   
    printSkipList(list);
    printf("List size: %d\n", sizeSkipList(list));
	
	/* Develop test cases for evaluating the following functions:  
	 int containsSkipList(struct skipList *slst, TYPE e) 
	 int removeSkipList(struct skipList *slst, TYPE e)
	 */

    /* Contains */
    printf("Contains %f? %d\n", val, containsSkipList(list, val));	
    printf("Contains 50? %d\n", containsSkipList(list, 50.0));
    
    /* Remove */
    printf("Remove 3.0\n");
    removeSkipList(list, 3.0);
    printSkipList(list);
    printf("List size: %d\n", sizeSkipList(list));
    
    /* merge list */
    printf("Merge\n");
    mergeSkipList(list, listB);
    printSkipList(list);

    /* Size */
    printf("Size: %d\n", sizeSkipList(list));

    /* listB */
    /*printf("ListB null ? %d\n", listB->topSentinel->value);*/
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

    /* Return 0 or 1 from rand() */
    return rand() % 2;
}

/* Move to the right as long as the next element is smaller than the input value:
 param: 	current -- pointer to a place in the list from where we need to slide to the right
 param:	e --  input value
 pre:	current is not NULL
 post: returns one link before the link that contains the input value e */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	
    /* Check if current is null */
    assert(current);

    while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	
	/* FIX ME */

    /* Return link before link that contains value e */
    return current;
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

    /* Check if slst is null */
    assert(slst);

    /* Declare and initialize skip list sentinel */
    slst->topSentinel = (struct skipLink*)malloc(sizeof(struct skipLink));
    assert(slst->topSentinel);
    slst->topSentinel->value = 0;
    slst->topSentinel->next = 0;
    slst->topSentinel->down = 0;

    /* Initialize skip list size to 0 */
    slst->size = 0;
}

/* Checks if an element is in the skip list:
 param: slst -- pointer to the skip list
 param: e -- 
element to be checked
 pre:	slst is not null
 post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e)
{
	/* FIX ME*/

    /* Check if slst is null */
    assert(slst);

    /* Loop through list if its not empty */
    if(sizeSkipList(slst) > 0)
    {
        /* Get the link before value e and compare */
        struct skipLink* curr = slst->topSentinel;

        while(1)
        {
            curr = slideRightSkipList(curr, e);
            
            /* Return true (1) if value e is found */
            if(curr->next && EQ(curr->next->value, e))
                return 1;

            else if(curr->down == 0)
                break;

            curr = curr->down;
        }
    }

    /* Return false (0) if value e is not found */
    return 0;
}


/* Remove an element from the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be removed
 pre:	slst is not null
 post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e)
{
	/* FIX ME*/

    /* Check if slst is null */
    assert(slst);

    /* Only remove elements if skip list is not empty */
    if(sizeSkipList(slst) > 0)
    {
        int foundLink = 0;
        struct skipLink* curr = slst->topSentinel;

        /* Slide right to find link before link with value e */
        while(1)
        {
            /* Slide right to find link before link with value e*/
            curr = slideRightSkipList(curr, e);

            /* If next link value is e, free it and fix link connections */
            if(curr->next && EQ(curr->next->value, e))
            {
                struct skipLink* tmp = curr->next;

                curr->next = curr->next->next;
                free(tmp);
                foundLink = 1;
            }

            /* Exit loop is on bottom list, down link is null */
            if(curr->down == 0)
                break;

            /* Set curr to down link */
            curr = curr->down;
        }

        if(foundLink)
        {
            slst->size--;

            /* Remove all empty lists */
            struct skipLink* head = slst->topSentinel;

            while(head->down)
            {
                if(head->next == 0)
                {
                    struct skipLink* downHead = head->down;
                    free(head);
                    slst->topSentinel = downHead;
                    head = downHead;
                }

                else
                    break;
            }
        }
    }
}



/* Add a new element to the skip list:
	param: slst -- pointer to the skip list
	param: e -- element to be added
	pre:	slst is not null
	post:	the new element is added to the lowest list and randomly to higher-level lists */
void addSkipList(struct skipList *slst, TYPE e)
{
    /* Check if slst is null */
    assert(slst);

	struct skipLink *downLink, *newLink;
	downLink = skipLinkAdd(slideRightSkipList(slst->topSentinel,e),e);
	
	/* FIX ME*/
    
    while(downLink)
    {
        /* Create new express lane with new head and new link */
        newLink = newSkipLink(e, 0, downLink);
        struct skipLink* newHead = newSkipLink(0, newLink, slst->topSentinel);

        /* Update the new skipList top sentinel to point to new list */
        slst->topSentinel = newHead;

        /* If need to make new list, update downLink, else set to null */
        if(flipSkipLink())
            downLink = newLink;

        else
            downLink = 0;
    }

    /* Increase size */
    slst->size++;
}


/* Find the number of elements in the skip list:
 param: slst -- pointer to the skip list
 pre:	slst is not null
 post: the number of elements */
int sizeSkipList(struct skipList *slst)
{
	
	/* FIX ME*/	

    /* Check if slst is null */
    assert(slst);

    /* Return size of slst */
    return slst->size;
}

/* Print the links in the skip list:
	param: slst -- pointer to the skip list
	pre:	slst is not null and slst is not empty
	post: the links in the skip list are printed breadth-first, top-down */
void printSkipList(struct skipList *slst)
{
	/* FIX ME*/

    /* Check if slst is null */
    assert(slst);

    /* Create link to currHead and currLink */
    struct skipLink* currHead = slst->topSentinel;
    struct skipLink* currLink = currHead;

    /* Loop over each link and print the value */
    while(currHead)
    {
        currLink = currLink->next;

        if(currLink)
            printf("%f\t", currLink->value);

        else
        {
            currHead = currHead->down;
            currLink = currHead;
            printf("\n");
        }
    }
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

    /* Check if slst1 and slst2 arm null */
    assert(slst1 && slst2);

    /* Check if slst1 and slst2 are empty */
    assert(sizeSkipList(slst1) > 0 && sizeSkipList(slst2) > 0);

    /* Get the head to the bottom list of slst2, the list that has all links */
    struct skipLink* head = slst2->topSentinel;
    struct skipLink* currLink = head;

    while(head->down)
        head = head->down;

    currLink = head->next;
    
    /* Loop through all links on bottom list */
    while(currLink)
    {
        /* Create variable to hold currLink value */
        TYPE currVal = currLink->value;

        /* If slst1 doesn't have currVal, add it */
        if(!containsSkipList(slst1, currVal))
            addSkipList(slst1, currVal);

        /* Remove all instances of currVal in slst2 */
        while(currLink && currVal == currLink->value)
        {
            currLink = currLink->next;
            removeSkipList(slst2, currVal);
        }
    }

    /* Free slst2 sentinel */
    free(slst2->topSentinel);
    slst2->topSentinel = 0;

    /* Free slst2 */
    free(slst2);
    slst2 = 0;
}
