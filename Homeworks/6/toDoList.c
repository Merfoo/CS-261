#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"

/* 
 * Gets the task priority from the file, reads until tab '\t', or EOF
 * Returns -1 if reaches EOF before reaching tab
 */
int getTaskPriority(FILE *filePtr)
{
    /* Create char array to hold task priority */
    int priorityMaxLen = 3;
    int priorityLen = 0;
    char priorityArr[3];

    /* Char to hold char in file */
    char c;

    /* Read numbers until tab or number limit reached */
    while((c = fgetc(filePtr)) != EOF && c != '\t')
    {
        if(priorityLen < priorityMaxLen && c != '\n')
            priorityArr[priorityLen++] = c;
    }
    
    /* Return -1 if reached EOF */
    if(c == EOF)
        return -1;

    /* Convert char to number */
    int i = priorityLen - 1;
    int numMod = 1;
    int priority = 0;

    for(i = priorityLen - 1; i >= 0; i--)
    {
        priority += (priorityArr[i] - '0') * numMod;
        numMod *= 10;
    }

    return priority;
}

/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */

    /* Check if heap and filePtr are null */
    assert(heap && filePtr);

    /* Check if heap is empty */
    assert(heap->data && sizeDynArr(heap) > 0);

    /* Write data from heap to file in order of priority */
    while(sizeDynArr(heap) > 0)
    {
        /* Get task with highest priority */
        TYPE task = getMinHeap(heap);
        
        /* Write contents of the task into the file */
        fprintf(filePtr, "%d\t%s\n", task.priority, task.description);
        
        /* Remove task from heap */
        removeMinHeap(heap);
    }
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */

    /* Check if heap and filePtr are null */
    assert(heap && filePtr);

    /* Read file for tasks */
    while(1)
    {
        /* Read priority */
        int priority = getTaskPriority(filePtr);

        if(priority == -1)
            break;

        /* Read description */
        char desc[TASK_DESC_SIZE];
        fgets(desc, TASK_DESC_SIZE, filePtr);

        /* Create a task from priority and description */
        struct Task task;
        strncpy(task.description, desc, TASK_DESC_SIZE);
        task.priority = priority;

        /* Add task to heap */
        addHeap(heap, task);
    }
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	/* FIX ME  */
    
    /* Check if heap is null and is empty */
    assert(heap && heap->data && sizeDynArr(heap) > 0);

    /* Creat tmp heap to store vals from heap when geting vals */
    DynArr *tmpHeap = (DynArr *) malloc(sizeof(DynArr));
    assert(tmpHeap);

    /* Copy heap data to tmpHeap */
    copyDynArr(heap, tmpHeap);

    /* Remove from heap, print it, add to tmp heap */
    while(sizeDynArr(tmpHeap) > 0)
    {
        struct Task task = getMinHeap(tmpHeap);
        removeMinHeap(tmpHeap);

        printf("%d\t%s\n", task.priority, task.description);
    }

    /* Free tmpHeap */
    deleteDynArr(tmpHeap);
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
