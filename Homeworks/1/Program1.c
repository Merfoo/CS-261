/* CS261- HW1 - Program1.c */
/* Name: Fauzi Kliman
 * Date: 4/8/16
 * Solution description: 
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
    /*Print the value of iptr*/
    printf("Value of iptr: %d\n", *iptr);

    /*Print the address pointed to by iptr*/
    printf("Address pointed to by iptr: %p\n", (void*)(&(*iptr)));     

    /*Print the address of iptr itself*/
    printf("Address of iptr: %p\n", (void *)&iptr);
}

int main(){     
    /*declare an integer x*/
    int x;

    /*print the address of x*/
    printf("Address of x: %p\n", (void *)&x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);    

    /*print the value of x*/
    printf("Value of x: %d\n", x);    

    return 0;
}
