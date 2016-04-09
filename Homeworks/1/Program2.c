/* CS261- HW1 - Program2.c*/
/* Name: Fauzi Kliman
 * Date: 4/8/16
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /* Increment a */
    (*a)++;    
    
    /* Decrement  b */
    (*b)--;

    /* Assign a-b to c */
    c = *a - *b;
    
    /* Return c */
    return c;
}

int main(){
    srand(time(NULL));

    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand()% 11;
    int y = rand()% 11;
    int z = rand()% 11;        

    /* Print the values of x, y and z */
    printf("x: %d\ny: %d\nz: %d\n", x, y, z);    

    /* Call foo() appropriately, passing x,y,z as parameters */
    int ret = foo(&x, &y, z);    

    /* Print the values of x, y and z */
    printf("x: %d\ny: %d\nz: %d\n", x, y, z);    

    /* Print the value returned by foo */
    printf("Return Value: %d\n", ret);

    /* Is the return value different than the value of z?  Why? */
    /* 
     * The return value will most likely be different as x, y, z
     * are initialized to random values between [0, 10] and the 
     * return value of foo is (a + 1) - (b - 1) and does nothing
     * with the 3rd parameter which is Z in this case. Thus the 
     * function is effectively (x + 1) - (y - 1)
     */      

    return 0;
}
    
    
