/* CS261- HW1 - Program5.c*/
/* Name: Fauzi Kliman
 * Date: 4/8/16
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
    /*Sort the n students based on their initials*/
    int i = 1;

    for(i = 1; i < n; i++)
    {
        struct student s = students[i];
        char curA = s.initials[0];
        char curB = s.initials[1];
        int j = i;

        while(j > 0)
        {
            char newA = students[j - 1].initials[0];
            char newB = students[j - 1].initials[1];

            if(curA < newA || (curA == newA && curB < newB))
            {
                students[j] = students[j - 1];
                j--;
            }

            else
                break;
        }

        students[j] = s;
    }
}

int main(){
    /* Seed pseudorandom number generator */
    srand(time(NULL));

    /*Declare an integer n and assign it a value.*/
    int n = 10;    

    /*Allocate memory for n students using malloc.*/
    struct student* s = (struct student*)malloc(sizeof(struct student) * n);
    
    /*Generate random IDs and scores for the n students, using rand().*/
    int i = 0;

    for(i = 0; i < n; i++)
    {
        s[i].initials[0] = rand() % 26 + 'A';
        s[i].initials[1] = rand() % 26 + 'A';
        s[i].score = rand() % 101;
    }    

    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; i++)
    {
        char initA = s[i].initials[0];
        char initB = s[i].initials[1];
        int score = s[i].score;

        printf("Student %c. %c., Score: %d\n", initA, initB, score); 
    }

    /*Pass this array along with n to the sort() function*/
    sort(s, n);
    printf("After sorted\n");   
 
    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; i++)
    {
        char initA = s[i].initials[0];
        char initB = s[i].initials[1];
        int score = s[i].score;

        printf("Student %c. %c., Score: %d\n", initA, initB, score); 
    }

    /* Free up the dynamic memory */
    free(s);
 
    return 0;
}
