/*
    Name: Fauzi Kliman    Date: 3/31/16
    Assignment: Test assignment
    Development Env: vim
*/

#include<stdio.h>

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

int main()
{
    int n = 0;

    while(1)
    {
        if(isPrime(n))
            printf("%d\n", n);
        
        n++;
    }

    return 0;
}
