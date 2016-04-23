#include "listbag.h"
#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*Function to get number of milliseconds elapsed since program started execution*/
double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
  if(argc==2)
    {
      struct bag* b = (struct bag*)malloc(sizeof(struct bag));/*Create new bag*/
      initBag(b);/*Initialize*/
      char* s=argv[1];
      int n = atoi(s);/*number of elements to add*/
      int i;
      for( i = 0 ; i < n; ++i)
    {
	    addToBag(b, (TYPE)(i));/*Add elements*/
    }
        addToBag(b, (TYPE)9);
        addToBag(b, (TYPE)3);
        addToBag(b, (TYPE)9);
     double t1 = getMilliseconds();/*Time before contains()*/
      printf("Found? %d\n", bagContains(b, (TYPE)20));
      double t2 = getMilliseconds();/*Time after contains()*/
        printf("Size: %d\n", b->l->size);
        removeFromBag(b, (TYPE)9);
        printf("Size: %d\n", b->l->size);
      printf("%d %g\n", n, t2-t1);
        freeBag(b);
    }
  else
    printf("Please enter the number of elements to add.\n");

  return 0;

}
