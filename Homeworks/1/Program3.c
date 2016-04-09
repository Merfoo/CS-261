/* CS261- HW1 - Program3.c*/
/* Name: Fauzi Kliman
 * Date: 4/8/16
 * Solution description:
 */

#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
    /*Allocate memory for ten students*/
    struct student* s = (struct student*)malloc(sizeof(struct student) * 10);
    assert(s);
 
    /*return the pointer*/
    return s;
}

void generate(struct student* students){
    assert(students);
    /*Generate random initials and scores for ten students.
        The two initial letters must be capital and must be between A and Z. 
        The scores must be between 0 and 100*/
    int i = 0;

    for(i = 0; i < 10; i++)
    {
        students[i].initials[0] = rand() % 26 + 'A';
        students[i].initials[1] = rand() % 26 + 'A';
        students[i].score = rand()% 101;
    }
}

void output(struct student* students){
    assert(students);
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/
    int i = 0;

    for(i = 0; i < 10; i++)
    {
        char initialsA = students[i].initials[0];
        char initialsB = students[i].initials[1];
        int score = students[i].score;

        printf("Student %d ", i + 1);
        printf("Initials: %c. %c., ", initialsA, initialsB);
        printf("Scores: %d\n", score);
    }
}

void summary(struct student* students){
    assert(students);
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = students[0].score;
    int max = min;
    int sum = min;
    int i = 1;

    for(i = 1; i < 10; i++)
    {
        int cur = students[i].score;
        sum += cur;

        if(cur < min)
            min = cur;

        else if(cur > max)
            max = cur;
    }
    
    printf("Minimum Score: %d\n", min);
    printf("Maximum Score: %d\n", max);
    printf("Average Score: %f\n", ((double)sum) / 10.0);
}

void deallocate(struct student* stud){
    /*Deallocate memory from stud*/
    free(stud);
    stud = NULL;
}

int main(){
    /* Set the seed for rand() */
    srand(time(NULL));

    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();    

    /*call generate*/
    generate(stud);    

    /*call output*/
    output(stud);    

    /*call summary*/
    summary(stud);    

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
