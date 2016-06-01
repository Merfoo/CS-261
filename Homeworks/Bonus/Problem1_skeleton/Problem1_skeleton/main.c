#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "avl.h"

int sumOfDiff(struct AVLnode *cur, int sum)
{
    if(!cur)
        return -1;

    int left = sum;
    int right = sum;

    printf("sum: %d\n", sum);

    if(cur->left)
    {
        printf("l: %d\n", cur->left->val);
        left = sumOfDiff(cur->left, sum + abs(cur->val - cur->left->val));
    }

    if(cur->right)
    {
        printf("r: %d\n", cur->right->val);
        right = sumOfDiff(cur->right, sum + abs(cur->val - cur->right->val));
    }

    if(cur->left && cur->right)
        return left < right ? left : right;

    if(cur->left)
        return left;

    return right;        
}

int getMinPath(struct AVLnode *cur, int i, int *path)
{
    if(!cur->left && !cur->right)
        return i;

    printf("%d\n", i);

    int curVal = cur->val;
    int left = -1;
    int right = -1;

    if(cur->left)
        left = sumOfDiff(cur->left, abs(curVal - cur->left->val));
    
    if(cur->right)
        right = sumOfDiff(cur->right, abs(curVal - cur->right->val));

    if(left != -1 && right != -1)
    {
        if( left < right)
        {
            path[i] = cur->left->val;
            return getMinPath(cur->left, i + 1, path);
        }

        else
        {
            path[i] = cur->right->val;
            return getMinPath(cur->right, i + 1, path);
        }
    }

    else if(left != -1)
    {
        path[i] = cur->left->val;
        return getMinPath(cur->left, i + 1, path);
    }

    else
    {
        path[i] = cur->right->val;
        return getMinPath(cur->right, i + 1, path);
    }
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
    i = getMinPath(cur, i, path);
	
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

    printf("%d\n", sumOfDiff(tree->root, 0));
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



