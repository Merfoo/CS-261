/*
    Name: Fauzi Kliman    Date: 3/31/16
    Assignment: Test assignment
    Development Env: vim
*/

#include<stdio.h>
#include "dynArray.h"

/*
  Description: Checks if an integer is a prime number
  Input: x, the integer to check if its prime
  Output: 1 if x is a prime number, 0 otherwise
*/
int isPrime(int x)
{
    if(x < 2)
        return 0;

    int i = 2;

    for(i = 2; i * i < x; i++)
        if(x % i == 0)
            return 0;

    return 1;
}

void printArr(DynArr* arr)
{
    int i = 0;

    for(i = 0; i < arr->size; i++)
        printf("%c   ", arr->data[i]);

    printf("\n");
}

int main()
{
    DynArr* arr = newDynArr(0);
    printf("%d :: %d\n", arr->size, arr->capacity);
    _dynArrSetCapacity(arr, arr->capacity * 2);
    printf("%d :: %d\n", arr->size, arr->capacity);
    printArr(arr);

    addDynArr(arr, 'a');
    printf("%d :: %d\n", arr->size, arr->capacity);
    addDynArr(arr, 'b');
    printf("%d :: %d\n", arr->size, arr->capacity);
    removeAtDynArr(arr, 0);
    addDynArr(arr, 'c');
    printf("%d :: %d\n", arr->size, arr->capacity);
    addDynArr(arr, 'd');
    printf("%d :: %d\n", arr->size, arr->capacity);
    addDynArr(arr, 'e');   
    printf("%d :: %d\n", arr->size, arr->capacity);
    printArr(arr);
    return 0;
    int n = 0;

    while(1)
    {
        if(isPrime(n))
            printf("%d\n", n);
        
        n++;
    }

    return 0;
}
