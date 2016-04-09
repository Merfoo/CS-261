/* CS261- HW1 - Program4.c*/
/* Name: Fauzi Kliman
 * Date: 4/8/16
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
    /*Sort the given array number, of length n*/
    int i = 1;

    for(i = 1; i < n; i++)
    {
        int cur = number[i];
        int j = i;

        while(j > 0 && cur < number[j - 1])
        {
            number[j] = number[j - 1];
            j--;
        }

        number[j] = cur;
    }
}

int main(){
    /* Seed pseudorandom number generator */
    srand(time(NULL));

    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int* numbers = (int*)malloc(sizeof(int) * n);
    
    /*Fill this array with random numbers, using rand().*/
    int i = 0;

    for(i = 0; i < n; i++)
        numbers[i] = rand();
 
    /*Print the contents of the array.*/
    for(i = 0; i < n; i++)
        printf("%d) %d\n", i + 1, numbers[i]);

    /*Pass this array along with n to the sort() function of part a.*/
    sort(numbers, n);
    
    /*Print the contents of the array.*/    
    for(i = 0; i < n; i++)
        printf("%d) %d\n", i + 1, numbers[i]);

    free(numbers);

    return 0;
}
