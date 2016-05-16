/*
  File: bst.c
  Implementation of the Binary Search Tree data structure.
 
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"


struct Node {
    TYPE         val;
    struct Node *left;
    struct Node *right;
};

struct BSTree {
    struct Node *root;
    int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
  function to initialize the binary search tree.
  param tree
  pre: tree is not null
  post:	tree size is 0
  root is null
*/

void initBSTree(struct BSTree *tree)
{

  /* FIX ME */

    /* Check if tree is null */
    assert(tree);

    /* Set tree root to null (0) */
    tree->root = 0;

    /* Set tree size to 0 */
    tree->cnt = 0;
}

/*----------------------------------------------------------------------------*/
/*
  function to create a binary search tree.
  param: none
  pre: none
  post: tree->count = 0
  tree->root = 0;
*/
struct BSTree*  newBSTree()
{
    struct BSTree *tree = malloc(sizeof(struct BSTree));
    assert(tree != 0);

    initBSTree(tree);
    return tree;
}

/*----------------------------------------------------------------------------*/
/*
  function to recursively free the nodes of a binary search tree
  param: node -- the root node of the tree to be freed
  pre: none
  post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
    /* FIX ME */

    /* If node is not null, delete its children first */
    if(node)
    {
        _freeBST(node->left);
        _freeBST(node->right);

        if(node->val)
        {
            free(node->val);
            node->val = 0;
        }
        
        free(node); 
    }
}

/*----------------------------------------------------------------------------*/
/*
  function to clear the nodes of a binary search tree
  param: tree    a binary search tree
  pre: tree ! = null
  post: the nodes of the tree are deallocated
  tree->root = 0;
  tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
    _freeBST(tree->root);
    tree->root = 0;
    tree->cnt  = 0;
}

/*----------------------------------------------------------------------------*/
/*
  function to deallocate a dynamically allocated binary search tree
  param: tree   the binary search tree
  pre: tree != null;
  post: all nodes and the tree structure itself are deallocated.
*/
void deleteBSTree(struct BSTree *tree)
{
    clearBSTree(tree);
    free(tree);
}


/*----------------------------------------------------------------------------*/
/*
  function to determine if  a binary search tree is empty.

  param: tree    the binary search tree
  pre:  tree is not null
*/
int isEmptyBSTree(struct BSTree *tree) { 
   return (tree->cnt == 0); 
}

/*
  function to determine the size of a binary search tree

  param: tree    the binary search tree
  pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { 
   return tree->cnt; 
}

/*----------------------------------------------------------------------------*/
/*
  recursive helper function to add a node to the binary search tree.
  this helper function does not increment tree->cnt.
  HINT: You have to use the compare() function to compare values.
  param:  cur	the current root node
  val	the value to be added to the binary search tree
  pre:	val is not null
*/
struct Node *_addNode(struct Node *cur, TYPE val)
{
   /*  FIX ME */

    /* If cur is null, create new link with value val */
    if(!cur)
    {
        cur = (struct Node*)malloc(sizeof(struct Node));
        assert(cur);
        cur->left = 0;
        cur->right = 0;
        cur->val = val;
    }

    else
    {
        /* Val is < than current nodes val, thus move left in tree */
        if(compare(val, cur->val) == -1)
            cur->left = _addNode(cur->left, val);

        /* Val is >= than current nodes val, thus move right in tree */
        else
            cur->right = _addNode(cur->right, val);
    }

    return cur;
}

/*----------------------------------------------------------------------------*/
/*
  function to add a value to the binary search tree
  param: tree   the binary search tree
  val		the value to be added to the tree

  pre:	tree is not null
  val is not null
  pose:  tree size increased by 1
  tree now contains the value, val
*/
void addBSTree(struct BSTree *tree, TYPE val)
{
    tree->root = _addNode(tree->root, val);
    tree->cnt++;
}

/*----------------------------------------------------------------------------*/
/*
  function to determine if the binary subtree contains an element
  HINT: You have to use the compare() function to compare values.
  param		cur: the root node of the subtree to be searched
  val		the value to search for in the tree
  pre:	tree is not null
  val is not null
  post:	none
*/
int containsBSTree(struct Node *cur, TYPE val)
{
   /*  FIX ME */

    /* Loop through each node checking its nodes value, then its childerens */
    while(cur)
    {
        /* Get compare value from compare function */
        int compareVal = compare(cur->val, val);

        /* Return true (1) if cur node val == val */
        if(compareVal == 0)
            return 1;

        /* Else if cur node val < val travel to right node */
        else if(compareVal == -1)
            cur = cur->right;

        /* Else cur node val > val travel to left node */
        else
            cur = cur->left;        
    }

    /* Return false (0) since no node val matched val */
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
  helper function to find the left most child of a node
  return the leftmost child of cur
  param: cur	the current node
  pre:	cur is not null
  post: none
*/
struct Node* _leftMost(struct Node *cur)
{
   /*  FIX ME */

    /* Check if cur is null */
    assert(cur);

    /* Loop left childs node */
    while(cur->left)
        cur = cur->left;

    /* Return left most child, cur */
    return cur;
}

/*----------------------------------------------------------------------------*/
/*
  recursive helper function to remove the left most child of a node
  HINT: this function returns cur if its left child is NOT NULL. Otherwise,
  it returns the right child of cur and free cur.

  Note:  If you do this iteratively, the above hint does not apply.

  param: cur	the current node
  pre:	cur is not null
  post:	the left most node of cur is not in the tree
*/
struct Node *_removeLeftMost(struct Node *cur)
{
    /*  FIX ME */

    /* Check if cur is null */
    assert(cur);

    /* If left is null, free cur and return right */
    if(!cur->left)
    {
        struct Node* tmp = cur->right;
        free(cur);
        return tmp;
    }

    /* If left is not null, remove left most and return cur */
    else if(cur->left)
    {
        struct Node* beforeLeft = cur;

        while(beforeLeft->left->left)
            beforeLeft = beforeLeft->left;

        struct Node* leftRight = beforeLeft->left->right;
        free(beforeLeft->left);
        beforeLeft->left = leftRight;
        return cur;
    }

    /* Should have returned before here */
    return 0;
}

/*----------------------------------------------------------------------------*/
/*
  recursive helper function to remove a node from the tree.
  this function does not decrease tree->cnt.
  HINT: You have to use the compare() function to compare values.
  param:	cur	the current node
  val	the value to be removed from the tree
  pre:	val is in the tree
  cur is not null
  val is not null
*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
   /*  FIX ME */

    /* If cur is null that means val is not in the tree, print error msg */
    if(!cur)
    {
        printf("WARNING: val not found in BSTree\n");
        return 0;
    }

    int compareVal = compare(cur->val, val);

    /* If cur val matches val replace it with left most of right child */
    if(compareVal == 0)
    {
        /* If cur is a leaf just remove it */
        if(!cur->left && !cur->right)
        {
            free(cur);
            return 0;
        }

        /* If cur has a right child, replace cur val right left most right */
        else if(cur->right)
        {
            struct Node* leftMost = _leftMost(cur->right);

            cur->val = leftMost->val;
            cur->right = _removeLeftMost(cur->right);
        }

        /* Else, replace cur val with left child */
        else
        {
            struct Node* left = cur->left;
            cur->val = left->val;
            cur->left = left->left;
            cur->right = left->right;
            free(left);
        }
    }

    /* If cur val < val go to right child */
    else if(compareVal == -1)
        cur->right = _removeNode(cur->right, val);

    /* Else, cur val > val go to left child */
    else
        cur->left = _removeNode(cur->left, val);

    return cur;
}

/*----------------------------------------------------------------------------*/
/*
  function to remove a value from the binary search tree
  param: tree   the binary search tree
  val		the value to be removed from the tree
  pre:	tree is not null
  val is not null
  val is in the tree
  pose:	tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, TYPE val)
{
    if (containsBSTree(tree->root, val)) {
	tree->root = _removeNode(tree->root, val);
	tree->cnt--;
    }
}

/*----------------------------------------------------------------------------*/
/* The following is used only for debugging, set to "#if 0" when used 
   in other applications */
#if 1
#include <stdio.h>

void printNode(struct Node *cur) {
    if (cur == 0)
	return;
    printf("(");
    printNode(cur->left);	 
    /*Call print_type which prints the value of the TYPE*/
    print_type(cur->val);
    printNode(cur->right);
    printf(")");
}

void printTree(struct BSTree *tree) {
    if (tree == 0)
	return;	 
    printNode(tree->root);	 
    printf("\n");
}
/*----------------------------------------------------------------------------*/

#endif


/************************************************************************************************************************
From here to the end of this File are a set of Functions for testing the Functions of the BST
***************************************************************************************************************************/
/*
  Function to built a Binary Search Tree (BST) by adding numbers in this specific order
  the graph is empty to start: 90, 10, 5, 50, 55, 40, 100, 

*/
struct BSTree *buildBSTTree() {
    /*       90
	 10     100
       5   50       110
         40  55   105 
                    106	
    */
    struct BSTree *tree	= newBSTree();		
    struct data *myData;

    /*Generate new Nodes and add them to the tree.*/
    myData =  malloc(sizeof(struct data));
    myData->number = 90;
    myData->name = "Root";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 10;
    myData->name = "Root->L";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 5;
    myData->name = "Root->L->L";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 50;
    myData->name = "Root->L->R";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 55;
    myData->name = "Root->L->R->R";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 40;
    myData->name = "Root->L->R->L";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 100;
    myData->name = "Root->R";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 110;
    myData->name = "Root->R->R";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 105;
    myData->name = "Root->R->R->L";
    addBSTree(tree, myData);

    myData = malloc(sizeof(struct data));
    myData->number = 106;
    myData->name = "Root->R->R->L->R";
    addBSTree(tree, myData);

    return tree;
}

