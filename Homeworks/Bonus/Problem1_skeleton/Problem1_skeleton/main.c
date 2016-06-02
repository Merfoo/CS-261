#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "avl.h"

int sumOfDiff(struct AVLnode *cur, int sum, int i, int *diffs)
{
    if(!cur)
        return -1;

    int left = sum;
    int right = sum;
    int leftChild = (i * 2) + 1;
    int rightChild = (i * 2) + 2;

    /*printf("sum: %d\n", sum);*/

    if(cur->left)
    {
        /*printf("l: %d\n", cur->left->val);*/
        int newSum = sum + abs(cur->val - cur->left->val);
        left = sumOfDiff(cur->left, newSum, leftChild, diffs);
    }

    if(cur->right)
    {
        /*printf("r: %d\n", cur->right->val);*/
        int newSum = sum + abs(cur->val - cur->right->val);
        right = sumOfDiff(cur->right, newSum, rightChild, diffs);
    }
    
    diffs[leftChild] = cur->left ? left : -1;
    diffs[rightChild] = cur->right ? right : -1;

    if(cur->left && cur->right)
        return left < right ? left : right;

    if(cur->left)
        return left;

    return right;        
}

int *calcDiffs(struct AVLTree *tree)
{
    int *diffs = (int *) malloc(sizeof(int) * tree->cnt);
    assert(diffs);

    diffs[0] = 0;
    sumOfDiff(tree->root, 0, 0, diffs);
    return diffs;
}

int getMinPath(struct AVLnode *cur, int *path, int *diffs)
{
    int len = 1;
    int parent = 0;
    
    while(1)
    {
        int leftChild = (parent * 2) + 1;
        int rightChild = (parent * 2) + 2;
        int left = diffs[leftChild];
        int right = diffs[rightChild];
        int leftSmaller = 1;

        /*printf("l: %d || r: %d\n", diffs[leftChild], diffs[rightChild]);*/
        if(cur->left && cur->right)
        {
            if(left < right)
                leftSmaller = 1;

            else
                leftSmaller = 0;
        }   

        else if(cur->left)
            leftSmaller = 1;

        else
            leftSmaller = 0;

        if(leftSmaller)
        {
            cur = cur->left;
            parent = leftChild;
        }

        else
        {
            cur = cur->right;
            parent = rightChild;
        }

        if(!cur)
            break;
        
        path[len++] = cur->val;
    }

    return len;
}

/* find minimum-cost path */
/* Input: pointer to tree
          pointer to array that should store all node values from
                  root to leaf along the identified min-cost path, 
   Output: min-cost path length 
*/
int FindMinPath(struct AVLTree *tree, int *path)
{
	struct AVLnode * cur = tree->root;
	int i = 1; /* counts the number of nodes along a path */

	/* write this function */
    int *diffs = calcDiffs(tree);
    i = getMinPath(cur, path, diffs);

	return i;
}

int main()
{
	const char *filename = "input.txt";
	FILE *file;
	int num, len, i;
	clock_t timer;
	int pathArray[50];

	struct AVLTree *tree = newAVLTree(); /*return an empty tree */
	
	file = fopen(filename, "r");
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}

	timer = clock();

	/* Find the minimum-cost path in the AVL tree*/
	pathArray[0] = tree->root->val;
	len = FindMinPath(tree, pathArray);

	/* Print out all numbers on the minimum-cost path */
	printf("The minimum-cost path is: ");
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	fclose(file);
	timer = clock() - timer;
	printf("\nExecution time is %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	deleteAVLTree(tree); 
}



